/*
 * Copyright (c) by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Header: /files/homes/master/cvs/hoops_master/shared/stream_common/BEdgeBreakerCompress.cpp,v 1.130 2010-01-21 23:37:55 covey Exp $
 * 
 * This file implements Jarek Rossignac's edgebreaker paper.
 * Variations from his algorithm are as follows:
 *    marks to indicate loops are associated with vertices only
 *    every loop is given a unique identifier
 *    preprocess during decompression uses stack state rather than his variable, "D"
 *    loop marks are associated with vertices only
 *    CASE_M's are eliminated using hole-plugging dummy vertices
 *    handles (topological genus > 0) are eliminated by splitting the surface at the 
 *       bounding loop at the time that the handle is discovered.
 */
#include <stdlib.h>
#include <memory.h>
#include "BStream.h"
#include "BInternal.h"
#include "BEdgeBreaker.h"
#include "vwrapper_stream.h"


#ifndef BSTREAM_READONLY
#ifndef BSTREAM_DISABLE_EDGEBREAKER


#if defined (DEBUG) && !defined (_WIN32_WCE)
  #include <assert.h>
  #define ASSERT(x) do { if( !(x) ) { assert(0); status = STATUS_ERROR; goto done; } } while(0)
  #define LABEL(x) x
  #include <stdio.h>
  static FILE *fp = NULL;
  static int debug;
  #if 0
    #ifdef _MSC_VER
      #define COMPLAIN(x) OutputDebugString(x)
    #else
      #define COMPLAIN(x) printf("%s",x)
    #endif
  #else
    #define COMPLAIN(x)
  #endif
#else
  #define ASSERT(x)
  #define LABEL(x)
  #define COMPLAIN(x)
#endif


/* The face lookup structure stores the array indices for all of the faces
 * that reference a given vertex. */
typedef struct {
    int *edges;
    int e_allocated;
    int e_used;
} vertex;


#ifdef STREAM_BIGENDIAN
    static int swap32( int in ){
        int out;
        /* mask to low byte to avoid sign-extension problems */
        out =  (in >> 24) & 0x000000ff; 
        out |= (in & 0x00ff0000) >> 8;
        out |= (in & 0x0000ff00) << 8;
        out |= in << 24;
        return out;
    }
    /* the macro is more efficient, but be careful of
     * call-by-name side effects */
    #define SWAP32(i) (\
            (((i) >> 24) & 0x000000ff) |\
            (((i) & 0x00ff0000) >> 8) |\
            (((i) & 0x0000ff00) << 8) |\
            ((i) << 24) \
            )

    static INT16 swap16( INT16 in ){
        INT16 out;
        out =  (in >> 8) & 0x00ff;
        out |= in << 8;
        return out;
    }
#else
    #define swap32(i) (i)
    #define SWAP32(i) (i)
    #define swap16(i) (i)
#endif


static int mtable_info_append_dummy( mtable_info alter *m, int d ) 
{
    int status = STATUS_NORMAL;

    if( m->dummies_used >= m->dummies_allocated ) {
        int i, *temp;
        if( m->dummies_allocated < 2)
            m->dummies_allocated = 2;
        else
            m->dummies_allocated *= 2;
        temp = (int *) malloc (m->dummies_allocated * sizeof( int ) );
        if( temp == NULL ) {
            COMPLAIN("temp array allocation failed in function mtable_info_append_dummy" );
            status = STATUS_ERROR;
            goto done;
        }
        if( m->dummies ) {
            for( i = 0 ; i < m->dummies_used ; i++ )
                temp[i] = m->dummies[i];
            free( m->dummies );
        }
        m->dummies = temp;
    }
    m->dummies[ m->dummies_used++ ] = d;
    done:
    return status;
}

static int mtable_info_append_patch( mtable_info alter *m, int p ) 
{
    int status = STATUS_NORMAL;
    if( m->patches_used >= m->patches_allocated ) {
        int i, *temp;
        if( m->patches_allocated < 2 )
            m->patches_allocated = 2;
        else
            m->patches_allocated *= 2;
        temp = (int *) malloc (m->patches_allocated * sizeof( int ) );
        if( temp == NULL ) {
            COMPLAIN("temp array allocation failed in function mtable_info_append_patch" );
            status = STATUS_ERROR;
            goto done;
        }
        if( m->patches ) {
            for( i = 0 ; i < m->patches_used ; i++ )
                temp[i] = m->patches[i];
            free( m->patches );
        }
        m->patches = temp;
    }
    m->patches[ m->patches_used++ ] = p;
    done:
    return status;
}


static int vertex_init( vertex alter *v )
{
    int status = STATUS_NORMAL;
    v->e_allocated = 8;
    v->edges = (int *) malloc (v->e_allocated * sizeof( int ));
    v->e_used = 0;
    if( v->edges == NULL ) {
        COMPLAIN( "vertex init allocation failed" );
        ASSERT( v->edges != NULL );
        status = STATUS_ERROR;
    }
    LABEL(done:);
    return status;
}


static void vertex_free( vertex alter *v )
{
    free( v->edges );
    v->edges = NULL;
}


int vertex_expand( vertex alter *v ) {
    int status = STATUS_NORMAL;
    int *temp;
    int i;

    if( v->e_allocated >= v->e_used ) {
        if( v->e_allocated < 2 )
            v->e_allocated = 2;
        else
            v->e_allocated *= 2;
        temp = (int *) malloc (v->e_allocated * sizeof( int ));
        if( temp == NULL ) {
            COMPLAIN( "vertex edge ref expand allocation failed" );
            ASSERT( temp != NULL );
            status = STATUS_ERROR;
            goto done;
        }
        if( v->edges ) {
            for( i = 0 ; i < v->e_used ; i++ )
                temp[i] = v->edges[i];
            free( v->edges );
        }
        v->edges = temp;
    }
    done:
    return status;
}

static int vertex_append_edge( vertex alter *v, int index, int *edge_out )
{
    int status = STATUS_NORMAL;

    if( v->edges == NULL )
        status = vertex_init( v );
    else if( v->e_used == v->e_allocated )
        status = vertex_expand( v );
    v->edges[ v->e_used++ ] = index;
    if( edge_out != NULL )
        *edge_out = v->e_used++;
    return status;
}


/* after remapping vertices, edges might be referenced from vertices
 * where they don't belong.  Here we repair that problem.*/
static void fix_edge_references( vertex alter *v_array, int src, half_edge_array const *ea ) 
{
    int i;
    vertex *from, *to;

    if( VERTEX_SPECIAL(src) )
        src = EA_VERTEX_INDEX(src);
    from = v_array + src;
    /* count backwards because we're modifying the end of the array inside 
     * the loop. */
    for( i = from->e_used - 1 ; i >= 0 ; i-- ) {
        if( ea->edges[ from->edges[ i ] ].start != src ) {
            to = v_array + ea->edges[ from->edges[ i ] ].start;
            vertex_append_edge( to, from->edges[ i ], NULL );
            from->edges[ i ] = from->edges[ from->e_used - 1 ];
            from->e_used--;
        }
    }
}



/*  */


/* remap_vertex
 * repairs non-manifold regions of the mesh splitting vertices into two 
 * the parameter, "a" is an example of one edge touches the vertex to be remapped
 */
static int remap_vertex( 
        half_edge_array const *ea, half_edge alter *a, 
        int old_id, int new_id)
{
    int ai, bi;  /* the index of a and b */
    int status = STATUS_NORMAL;

    ai = (int)(a - ea->edges);
    ASSERT( validate_edge( ea, ea->edges + ai, NULL ) );
    if( ea->edges[ai].start != old_id ) {
        /* we're remapping the vertex at the end of the given edge, a */
        ai = HNEXT(ai);
    }
    ASSERT( validate_edge( ea, ea->edges + ai, NULL ) );
    ASSERT( ea->edges[ai].start == old_id );
    ea->edges[ai].start = new_id;
    bi = ai;
    /* walk around the vertex clockwise */
    while( !EDGE_INVALID( ea->edges[bi].twin ) ) {
        bi = ea->edges[bi].twin;
        bi = HNEXT(bi);
        ASSERT( ea->edges[bi].start == old_id );
        ea->edges[bi].start = new_id;
        if( bi == ai ) 
            break;
    }
    if( EDGE_INVALID( ea->edges[bi].twin ) ) {
        /* now counterclockwise (unless we ended where we started) */
        bi = HPREV(ai);
        bi = ea->edges[bi].twin;
        while( !EDGE_INVALID( bi )  ) { 
            ea->edges[bi].start = new_id;
            bi = HPREV(bi);
            bi = ea->edges[bi].twin;
        } 
    }
    ASSERT( validate_edge( ea, ea->edges + ai, NULL ) );

    LABEL(done:);
    return status;
 
} /* end function remap_vertex */



/* pack_mtable
 * defines the format in which the mtable is to be stored.  
 * Must be carefully matched with the unpack.
 * See declaration of the mtable_info structure for a description of the format */
static int pack_mtable( mtable_info const *m, void alter *target, int alter *size )
{
    int status = STATUS_NORMAL;
    int *out = (int *)target;
    int i, prev_patch, prev_dummy;
    int flags = 0, temp;

    if( m->mlengths_used ) flags |= MTABLE_HAS_LENGTHS;                 /* obsolete */
    if( m->m2stackoffsets_used ) flags |= MTABLE_HAS_M2STACKOFFSETS;    /* obsolete */
    if( m->m2gateoffsets_used ) flags |= MTABLE_HAS_M2GATEOFFSETS;      /* obsolete */
    if( m->dummies_used ) flags |= MTABLE_HAS_DUMMIES;
    if( m->patches_used ) flags |= MTABLE_HAS_PATCHES;
    if( m->bounding != NULL ) flags |= MTABLE_HAS_BOUNDING;
    if( (m->x_quantization != DEFAULT_QUANTIZATION) ||
        (m->y_quantization != DEFAULT_QUANTIZATION) ||
        (m->z_quantization != DEFAULT_QUANTIZATION) )
        flags |= MTABLE_HAS_QUANTIZATION;
    if( (m->x_quantization_normals != DEFAULT_QUANTIZATION) ||
        (m->y_quantization_normals != DEFAULT_QUANTIZATION) ||
        (m->z_quantization_normals != DEFAULT_QUANTIZATION) )
        flags |= MTABLE_HAS_QUANTIZATION_NORMALS;

    *out++ = swap32(flags);
    if( m->mlengths_used ) *out++  = swap32(m->mlengths_used);              /* obsolete */
    if( m->m2stackoffsets_used ) *out++ = swap32(m->m2stackoffsets_used);   /* obsolete */
    if( m->dummies_used ) *out++ = swap32(m->dummies_used);
    if( m->patches_used ) *out++ = swap32(m->patches_used);
    for( i = 0 ; i < m->mlengths_used ; i++ )
        *out++ = swap32(m->mlengths[i]);
    for( i = 0 ; i < m->m2stackoffsets_used ; i++ )
        *out++ = swap32(m->m2stackoffsets[i]); 
    for( i = 0 ; i < m->m2gateoffsets_used ; i++ )
        *out++ = swap32(m->m2gateoffsets[i]); 

    /* dummy notations and the first half of patches are monotonically
     * increasing.  Encode them as relative to the previous entry */
    prev_dummy = 0;
    for( i = 0 ; i < m->dummies_used ; i++ ) {
        *out++ = swap32(m->dummies[i] - prev_dummy); 
        prev_dummy = m->dummies[i];
    }
    ASSERT( (m->patches_used % 2) == 0 );
    prev_patch = 0;
    for( i = 0 ; i < m->patches_used ; i += 2 ) {
        *out++ = swap32(m->patches[i] - prev_patch);
        prev_patch = m->patches[i];
        *out++ = swap32(m->patches[i + 1]); 
    }
    if( m->bounding != NULL ) {
        temp = *((int *) &m->bounding->x1);
        *out++ = swap32(temp);
        temp = *((int *) &m->bounding->y1);
        *out++ = swap32(temp);
        temp = *((int *) &m->bounding->z1);
        *out++ = swap32(temp);
        temp = *((int *) &m->bounding->x2);
        *out++ = swap32(temp);
        temp = *((int *) &m->bounding->y2);
        *out++ = swap32(temp);
        temp = *((int *) &m->bounding->z2);
        *out++ = swap32(temp);
    }
    if( flags & MTABLE_HAS_QUANTIZATION ) {
        *out++ = swap32(m->x_quantization);
        *out++ = swap32(m->y_quantization);
        *out++ = swap32(m->z_quantization);
    }
    if( flags & MTABLE_HAS_QUANTIZATION_NORMALS ) {
        *out++ = swap32(m->x_quantization_normals);
        *out++ = swap32(m->y_quantization_normals);
        *out++ = swap32(m->z_quantization_normals);
    }

    if( size != NULL )
        *size = (int)((char *)out - (char *)target);
    LABEL(done:);
    return status;

} /* end function pack_mtable */


#define quantize_normals(a,b,c,d,e,f,g) quantize_points(a,b,c,d,e,f,g)

static int quantize_points(
        ET_Bounding const *bbox, int pcount, float const *points,       /* input */
        int x_quantization, int y_quantization, int z_quantization,     /* input */
        int alter *quantized_points )        /* output */
{ 
    int status = STATUS_NORMAL;
    int i;
    float xrange, yrange, zrange;
    int xmaxval, ymaxval, zmaxval;
    
    xmaxval = (1<<x_quantization)-1;
    ymaxval = (1<<y_quantization)-1;
    zmaxval = (1<<z_quantization)-1;
    if( bbox->x1 == bbox->x2 )
        xrange = 0;
    else
        xrange = ((float) xmaxval ) / (bbox->x2 - bbox->x1);
    if( bbox->y1 == bbox->y2 )
        yrange = 0;
    else
        yrange = ((float) ymaxval ) / (bbox->y2 - bbox->y1);
    if( bbox->z1 == bbox->z2 )
        zrange = 0;
    else
        zrange = ((float) zmaxval ) / (bbox->z2 - bbox->z1);
    for( i = 0 ; i < pcount ; i++ ) {
        quantized_points[ i*3 + 0 ] = (int) ((points[ i*3 + 0 ] - bbox->x1) * xrange + 0.5f);
        quantized_points[ i*3 + 1 ] = (int) ((points[ i*3 + 1 ] - bbox->y1) * yrange + 0.5f);
        quantized_points[ i*3 + 2 ] = (int) ((points[ i*3 + 2 ] - bbox->z1) * zrange + 0.5f);
    }
    return status;
}


#ifdef DEBUG
int tristrip_decodes_correctly( int const *tristrip, int start_ei, half_edge_array const *ea, vhash_t *proxy_hash ) 
{   
    int status = STATUS_NORMAL;
    int i, ei, v, proxyv, strip_len;

    //tristrip[0] < 0 means that this is really a triangle fan.
    if( tristrip[0] > 0 ) {
        strip_len = tristrip[0];
        ei = start_ei;
        v = ea->edges[ei].start;
        if( v != tristrip[1] ) { 
            proxyv = PROXY_VERTEX_INDEX(proxy_hash,v);
            if( proxyv != tristrip[1] )
                ASSERT(0); 
        }
        v = ea->edges[HNEXT(ei)].start;
        if( v != tristrip[2] ) { 
            proxyv = PROXY_VERTEX_INDEX(proxy_hash,v);
            if( proxyv != tristrip[2] )
                ASSERT(0); 
        }
        ei = HNEXT(ei);
        i = 3;
        for(;;) {
            if( ea->edges[HNEXT(ei)].start != tristrip[i] ) { 
                v = ea->edges[HNEXT(ei)].start;
                proxyv = PROXY_VERTEX_INDEX(proxy_hash,v);
                if( proxyv != tristrip[i] ) {
                    ASSERT(0); 
                }
            }
            if( i == strip_len ) 
                break;
            i++;

            ASSERT( ea->edges[ei].twin != GARBAGE_EDGE );
            ei = ea->edges[ei].twin;
            ei = HPREV(ei);
			/* sweep under rug: huge negative array indices work on 32-bit systems using black magic, but not on 64-bit ones */ 
			ei &= ~0x80000000;

            if( ea->edges[ei].start != tristrip[i] ) { 
                v = ea->edges[ei].start;
                proxyv = PROXY_VERTEX_INDEX(proxy_hash,v);
                if( proxyv != tristrip[i] ) {
                    ASSERT(0); 
                }
            }
            if( i == strip_len ) 
                break;
            i++;  

            ASSERT( ea->edges[ei].twin != GARBAGE_EDGE );
            ei = ea->edges[ei].twin;
            ei = HNEXT(ei);
        }
    }
    else {
        strip_len = -tristrip[0];
        ASSERT(0); //xxx we are not ready to handle trifans yet.
    }
  LABEL(done:);
    return status;
}
#endif


/* pack_points_and_normals
 * returns >0 on success, <=0 on failure */
static int pack_points_and_normals( 
        edgebreaker_header alter *hptr,
        half_edge_array const *ea, 
        int original_pcount, 
        int pcount, 
        int *quantized_points,
        int *quantized_normals,
        char const *dummies,
        vhash_t *proxy_hash,
        bool by_tristrips, 
        vhash_t *tristrip_hash, 
        int buffsize, 
        void alter *buffer_out )
{
    int status = STATUS_NORMAL;
    int_stack regular_edges, discontinuous_edges;
    int i, ei, k, v, v2, v3;
    char *touched = NULL;
    VArray<int> coords, normals;
    int *diffs = NULL, *p;
    int *ndiffs = NULL, *np;
    int diffs_count = 0, coords_count = 0;
    varstream vs;
    static const int bits[9] = { 2, 6, 10, 14, 18, 22, 26, 31, 32 };
    static const int bits2[3] = { 16, 31, 32 };
    /* when vertices are remapped, new vertices are created (eav) for the purpuse
     * of the half edge array, but borrow their location information from other 
     * proxy vertices (proxyv) */
    int eav, proxyv;
    char *ptr, *end;
    void *item;
    int *tristrip_ptr;
    VArray<int *> tristrip_start_ptr;
    VArray<int> tristrip_start_ei;
    VArray<int> tristrip_start_i;

	UNREFERENCED (original_pcount);
  
    if( !by_tristrips )
        tristrip_hash = NULL;
      
    if( !quantized_points && !quantized_normals && !tristrip_hash ) {
        hptr->pointslen = 0;
        hptr->normalslen = 0;
        return STATUS_NORMAL;
    }

    ASSERT( ea->visitations != NULL );
    touched = (char *) malloc( (pcount+1) * sizeof( char ) );
    memset( touched, 0, pcount * sizeof( char ) );
    /* point DUMMY_VERTEX in the proxy hash to a fake entry that declares itself already touched */
    touched[pcount] = 1;
    vhash_insert_item( proxy_hash, I2V(DUMMY_VERTEX), I2V(pcount) );
    if( quantized_points != NULL )
        diffs = (int *) malloc( 3 * pcount * sizeof( int ) );
    if( quantized_normals != NULL )
        ndiffs = (int *) malloc( 3 * pcount * sizeof( int ) );
    int_stack_init( &regular_edges );
    int_stack_init( &discontinuous_edges );
    for( i = 0 ; i < ea->visitations_used ; i++ ) {
        ei = ea->visitations[i];
        //note: on the compression side, tristrips always start on edge id's that are multiples of 3,
        //so we can dodge the hash lookup on others
        if( (ei%3 == 0) && (tristrip_hash != NULL) ) {
            if( vhash_lookup_item( tristrip_hash, I2V(ei), &item ) == VHASH_STATUS_SUCCESS ) {
                tristrip_ptr = (int *)item;
                tristrip_start_ptr.Append(tristrip_ptr);
                tristrip_start_ei.Append(ei);
                tristrip_start_i.Append(i);
            }
        }
        v = PROXY_VERTEX_INDEX(proxy_hash,ea->edges[ei].start);
        if( v == DUMMY_VERTEX )
            continue;
        if( touched[v] )
            continue;
        /* never start a traversal on a triangle that contains a dummy vertex */
        v2 = PROXY_VERTEX_INDEX(proxy_hash,ea->edges[HNEXT(ei)].start);
        v3 = PROXY_VERTEX_INDEX(proxy_hash,ea->edges[HPREV(ei)].start);
        if( v2 == DUMMY_VERTEX || v3 == DUMMY_VERTEX )
            continue;

        /* seed the traversal with a never-before-seen triangle. */
        for( k = 0 ; k < 3 ; k++ ) { 
            v = PROXY_VERTEX_INDEX(proxy_hash,ea->edges[ei].start);
            if( !touched[v] ) {
                touched[v] = 1; 
                /* append the current edge's start xyz */
                if( quantized_points )
                    coords.AppendArray( &quantized_points[v*3], 3 );
                if( quantized_normals )
                    normals.AppendArray( &quantized_normals[v*3], 3 );
            }
            /* add the current edges to the list of edges to be traversed */
            if( EDGE_INVALID( ea->edges[ei].twin ) ) {
                /* xxx TODO. I'd like to be able to traverse across non-garbage special twins,
                 * but that requires that the reading side have a few operations (e.g. zip) that
                 * are not yet in place.  note: there is a matching block inside the while loop 
                 * below. */
                //if( ea->edges[ei].twin != GARBAGE_EDGE )
                //    int_stack_push( &discontinuous_edges, REAL_EDGE_INDEX(ei) );
            }
            else
                int_stack_push( &regular_edges, ei );
            ei = HNEXT(ei);
        } 
            
        /* now traverse over the entirety of a contiguous piece, pushing untouched edges onto
         * the stack as we see them.  Where possible, favor crossing regular edges over
         * discontinuous ones */
        while( regular_edges.used || discontinuous_edges.used ) {
            if( regular_edges.used ) {
                ei = int_stack_pop( &regular_edges );
            }
            else {
                ei = int_stack_pop( &discontinuous_edges );
            }
            ei = ea->edges[ei].twin;
            v = ea->edges[HPREV(ei)].start;
            
            ASSERT( v != GARBAGE );
            if( VERTEX_SPECIAL(v) ) {
                /* eav is the unique id by which the half edge array knows this vertex */
                eav = EA_VERTEX_INDEX(v);
                /* proxyv is the other vertex from which this vertex borrows its location 
                 * (or DUMMY_VERTEX, if it's just there to plug a hole and therefore has no location) */
                proxyv = PROXY_VERTEX_INDEX(proxy_hash,v);
            }
            else
                eav = proxyv = v;
            ASSERT( eav >= 0 && (eav < pcount || eav < original_pcount) );
            if( proxyv == DUMMY_VERTEX )
                continue;
            ASSERT( proxyv >= 0 && proxyv < original_pcount );

            /* ei is the twin, v is the third vertex of the twin's triangle.
             * if that vertex hasn't been touched, we can assume that that triangle 
             * needs traversing.  Most new triangles push 2 new edges onto the stacks */
            if( !touched[proxyv] ) {
                //append a point
                if( quantized_points ) {
                    p = diffs + 3*diffs_count;
                    predict( ea, ei, proxyv, touched, proxy_hash, quantized_points, p );
                    p[0] -= quantized_points[proxyv*3 + 0];
                    p[1] -= quantized_points[proxyv*3 + 1];
                    p[2] -= quantized_points[proxyv*3 + 2];
                }
                if( quantized_normals ) {
                    np = ndiffs + 3*diffs_count;
                    //append a normal
                    predict( ea, ei, proxyv, touched, proxy_hash, quantized_normals, np );
                    np[0] -= quantized_normals[proxyv*3 + 0];
                    np[1] -= quantized_normals[proxyv*3 + 1];
                    np[2] -= quantized_normals[proxyv*3 + 2];
                }
                //increment the count
                diffs_count++;
                //push candidates to continue the traversal
                ei = HNEXT(ei);
                if( EDGE_INVALID( ea->edges[ei].twin ) ) {
                    //if( ea->edges[ei].twin != GARBAGE_EDGE )
                    //    int_stack_push( &discontinuous_edges, REAL_EDGE_INDEX(ei) );
                }
                else {
                    int_stack_push( &regular_edges, ei );
                }
                ei = HNEXT(ei);
                if( EDGE_INVALID( ea->edges[ei].twin ) ) {
                    //if( ea->edges[ei].twin != GARBAGE_EDGE )
                    //    int_stack_push( &discontinuous_edges, REAL_EDGE_INDEX(ei) );
                }
                else {
                    int_stack_push( &regular_edges, ei );
                }
                touched[proxyv] = 1;
            }
        }
    }
    
    ptr = (char *)buffer_out;
    end = ptr + buffsize;
    vsinit_write( &vs, buffsize, ptr );
    if( quantized_points != null )
        coords_count = coords.Count()/3;
    else
        coords_count = normals.Count()/3;
    //start the stream with a boolean flag to indicate that information to rebuild tristrips is contained
    vsput( &vs, bits, (tristrip_hash!=NULL) );
    vsput( &vs, bits2, coords_count );
    vsput( &vs, bits2, diffs_count );
    if( quantized_points ) {
        for( i = 0 ; i < coords_count ; i++ ) {
            vsput( &vs, bits2, coords[i*3] );
            vsput( &vs, bits2, coords[i*3+1] );
            vsput( &vs, bits2, coords[i*3+2] );
        }
        for( i = 0 ; i < diffs_count ; i++ ) {
            vsput( &vs, bits, diffs[i*3] );
            vsput( &vs, bits, diffs[i*3+1] );
            vsput( &vs, bits, diffs[i*3+2] );
        }
    }
    if( quantized_normals ) {
        for( i = 0 ; i < coords_count ; i++ ) {
            vsput( &vs, bits2, normals[i*3] );
            vsput( &vs, bits2, normals[i*3+1] );
            vsput( &vs, bits2, normals[i*3+2] );
        }
        for( i = 0 ; i < diffs_count ; i++ ) {
            vsput( &vs, bits, ndiffs[i*3] );
            vsput( &vs, bits, ndiffs[i*3+1] );
            vsput( &vs, bits, ndiffs[i*3+2] );
        }
    }
    if( (tristrip_hash != NULL) && 
        (tristrip_start_ptr.Count() != 0) ) {
        int strip_diff, count, code;

        ASSERT( tristrip_start_ptr.Count() == tristrip_start_ei.Count() &&
                tristrip_start_ei.Count() == tristrip_start_i.Count() );
        vsput( &vs, bits2, tristrip_start_ptr.Count() );
        // encode the edge id's 
        count = tristrip_start_ptr.Count();
        vsput( &vs, bits2, tristrip_start_i[0] );
        for( i = 1 ; i < count ; i++ ) {
            strip_diff = tristrip_start_i[i] - tristrip_start_i[i-1];
            vsput( &vs, bits2, strip_diff );
        }
        for( i = 0 ; i < count ; i++ ) {
            tristrip_ptr = tristrip_start_ptr[i];
            // tristrip lengths are always >= 3, trifans are always <= -3
            // trifans of length -3 are equivalent to tristrips of length 3, so we can 
            // safely encode the strip as 3 closer to 0 than it really is.
            if( tristrip_ptr[0] > 0 )
                code = tristrip_ptr[0] - 3;
            else
                code = tristrip_ptr[0] + 3;
            vsput( &vs, bits, code );
            ASSERT( tristrip_decodes_correctly( tristrip_ptr, tristrip_start_ei[i], ea, proxy_hash ) );
        }
    }
    if( vs.status == STATUS_ERROR ) {
        /* if the varstream overflowed, tell the caller to try again with a bigger buffer */
        status = STATUS_TRY_AGAIN;
        goto done;
    }
    
    hptr->pointslen = (vs.used + 1) * sizeof( int );        
    if( quantized_normals )
        hptr->normalslen = (vs.used + 1) * sizeof( int );  
        
    vsswap( &vs ); /* account for little/big endian */
    
  done:
    int_stack_free( &regular_edges );
    int_stack_free( &discontinuous_edges );
    if( touched )
        free( touched );
    if( diffs )
        free( diffs );
    if( ndiffs )
        free( ndiffs );
    UNREFERENCED(dummies);
    return status;
} 


static int old_pack_normals( 
        mtable_info *mtable, int alter *associations, edgebreaker_header *hptr,
        int original_pointcount, int const *pointmap, float const *normals, 
        int buffsize, void alter *buffer_out, 
        eb_compress_configs const *configs )
{
    int status = STATUS_NORMAL;
    int i;
    int p[3];
    int *quantized_normals = NULL;
    ET_Bounding bounding;
    float xrange, yrange, zrange;
    int xmaxval, ymaxval, zmaxval;
    varstream vs;
    int bits[8] = { 2, 6, 10, 14, 18, 22, 26, 31 };

    ASSERT( hptr->scheme >= 1 );
    ASSERT( hptr->normals_scheme == 0 );
    ASSERT( configs != NULL );
    xmaxval = MAXVAL(configs->x_quantization_normals);
    ymaxval = MAXVAL(configs->y_quantization_normals);
    zmaxval = MAXVAL(configs->z_quantization_normals);
    xrange = ((float) xmaxval ) / 2.0f;
    yrange = ((float) ymaxval ) / 2.0f;
    zrange = ((float) zmaxval ) / 2.0f;
    bounding.x1 = bounding.y1 = bounding.z1 = -1;
    bounding.x2 = bounding.y2 = bounding.z2 = 1;

    quantized_normals = (int *) malloc ( original_pointcount * 3 * sizeof( int ) );
    if( quantized_normals == NULL ) {
        COMPLAIN( "quantized_normals array allocation failed in function old_pack_normals()" );
        status = STATUS_ERROR;
        goto done;
    }

    for( i = 0 ; i < original_pointcount ; i ++ ) {
        quantized_normals[ i*3 + 0 ] = (int) ((normals[ i*3 + 0 ] - bounding.x1) * xrange + 0.5f);
        quantized_normals[ i*3 + 1 ] = (int) ((normals[ i*3 + 1 ] - bounding.y1) * yrange + 0.5f);
        quantized_normals[ i*3 + 2 ] = (int) ((normals[ i*3 + 2 ] - bounding.z1) * zrange + 0.5f);
    }


    vsinit_write( &vs, buffsize, buffer_out );
    for( i = 0 ; i < hptr->pcount ; i ++ ) {
        /* verify that a few assumptions have been maintained (debug only) */
        ASSERT( validate_associations( associations + i*3, original_pointcount ) );
        ASSERT( pointmap[i] != GARBAGE_VERTEX );
        ASSERT( quantized_normals[ pointmap[i]*3 + 0 ] <= xmaxval );
        ASSERT( quantized_normals[ pointmap[i]*3 + 1 ] <= ymaxval );
        ASSERT( quantized_normals[ pointmap[i]*3 + 2 ] <= zmaxval );
        /* predict where the new unknown point will lie in space */
        old_predict( associations + i*3, quantized_normals, &bounding, 
                configs->x_quantization_normals, configs->y_quantization_normals, configs->z_quantization_normals, p );

        /* encode the difference */
        vsput( &vs, bits, quantized_normals[ pointmap[i]*3 + 0 ] - p[0] );
        vsput( &vs, bits, quantized_normals[ pointmap[i]*3 + 1 ] - p[1] );
        vsput( &vs, bits, quantized_normals[ pointmap[i]*3 + 2 ] - p[2] );
    }

    /* if the varstream overflowed, tell the caller to try again with a bigger buffer */
    if( vs.status == STATUS_ERROR ) {
        status = STATUS_TRY_AGAIN;
        goto done;
    }
    hptr->normalslen = (vs.used + 1) * sizeof( int );
    vsswap( &vs ); /* account for little/big endian */


    done:
    /* no need to do a vsfree (we don't own the data pointer) */
    if( quantized_normals != NULL )
        free( quantized_normals );
    UNREFERENCED(mtable);
    return status;

} /* end function old_pack_normals */


static int loop_table_init( loop_table alter *ltable, int pcount_max, int edge_count )
{
    ltable->loops_edges_allocated = 0;
    ltable->loops = (int *) malloc ( pcount_max * sizeof(int) );
    if( ltable->loops == NULL )
        return STATUS_ERROR;
    memset( ltable->loops, 0, pcount_max * sizeof(int) );
    
    ltable->np_allocated = edge_count;
    ltable->P = (int *) malloc ( edge_count * sizeof(int) );
    if( ltable->P == NULL )
        return STATUS_ERROR;
    ltable->N = (int *) malloc ( edge_count * sizeof(int) );
    if( ltable->N == NULL )
        return STATUS_ERROR;
    return STATUS_NORMAL;
}

static void loop_table_free( loop_table alter *ltable )
{
    if( ltable->loops )
        free ( ltable->loops );
    if( ltable->loops_edges )
        free ( ltable->loops_edges );
    if( ltable->N )
        free ( ltable->N );
    if( ltable->P )
        free ( ltable->P );
}

static int loop_table_np_expand ( loop_table alter *ltable )
{
    int oldsize = ltable->np_allocated;
    int *temp;
    
    ltable->np_allocated = (int)(1.2 * ltable->np_allocated);

    temp = (int *) malloc ( ltable->np_allocated * sizeof(int) );
    memcpy( temp, ltable->P, oldsize * sizeof( int ) );
    memset( temp + oldsize, 0x80, (ltable->np_allocated - oldsize) * sizeof( int ) );
    free( ltable->P );
    ltable->P = temp;

    temp = (int *) malloc ( ltable->np_allocated * sizeof(int) );
    memcpy( temp, ltable->N, oldsize * sizeof( int ) );
    memset( temp + oldsize, 0x80, (ltable->np_allocated - oldsize) * sizeof( int ) );
    free( ltable->N );
    ltable->N = temp;

    return STATUS_NORMAL;
}






/* traverse
 * Put a mark on all the vertices that can be found by traversing the surface
 * starting at a particular vertex.  In other words, find all the vertices in
 * a given topologically distinct piece. */
static int traverse( 
    half_edge_array const *ea, 
    vertex const *v_array, 
    int const *loops,
    int startpoint_id,
    int alter *pieces, 
    int active,
    int_stack alter *loops_stack )
{
    int_stack seen;
    int i, id, end, ei;
    
    int_stack_init( &seen );
    int_stack_push( &seen, startpoint_id );
    while( seen.used != 0 ) {
        id = int_stack_pop( &seen );
        if( loops[ id ] != 0 )
            int_stack_push_if_unique( loops_stack, loops[id] );
        for( i = 0 ; i < v_array[id].e_used ; i++ ) {
            ei =  v_array[id].edges[i];
            end = ea->edges[ HNEXT(ei) ].start;
            if( pieces[ end ] == 0 ) {
                pieces[ end ] = active;
                int_stack_push( &seen, end );
            }
        }
    }
    int_stack_free( &seen );

    return 1;

} /* end function traverse */


/* find_pieces
 * For every vertex in the array, kick off a recursive traverse function if it
 * hasn't been touched yet.*/
static int find_pieces( 
    half_edge_array const *ea, 
    int newpcount, 
    vertex const *v_array, 
    int const *loops,
    int alter *pieces,
    int alter *num_pieces,
    int alter *loops_per_piece )
{
    int i, active = 0;
    int_stack loops_stack;

    for( i = 0 ; i < newpcount ; i++ ) {
        if( pieces[ i ] == 0 ) {
            active++;
            int_stack_init( &loops_stack );    
            traverse( ea, v_array, loops, i, pieces, active, &loops_stack );
            loops_per_piece[active] = loops_stack.used;
            int_stack_free( &loops_stack );    
        }
    }
    if( num_pieces != NULL )
        *num_pieces = active;
    return 1;

} /* end function find_pieces */


static int sort ( int *, int * ); /* forward declaration */

/* every vertex referenced in a loop should be unique (i.e. no "figure-8"'s) */
static int loop_is_manifold( 
        half_edge_array alter *ea, 
        int edge, 
        int count, 
        int alter *duplicate, 
        loop_table const *ltable  )
{
    int i, bi;
    int status = 0;
    int is_manifold = 1;
    half_edge *b;
    int *verts;
    int const *N = ltable->N;

    /* if we weren't given a valid count, calculate one */
    if( count <= 0 ) {
        bi = edge;
        count = 0;
        ASSERT( !EDGE_INVALID( N[bi] ) );
        ASSERT( validate_edge( ea, ea->edges + edge, ltable ) );
        do{
            bi = N[bi];
            count++;
        } while( bi != edge );
    }
    /* a closed loop has as many vertices as edges */
    verts = (int *) malloc( count * sizeof( int ) );
    if( verts == NULL ) 
        goto done; /* allocation failed.  This one can slide, though. */
    /* put the vertex id's into an array */
    bi = edge;
    b = ea->edges + edge;
    i = 0;
    do{
        verts[i] = ea->edges[bi].start;
        bi = N[bi];
        i++;
    } while( bi != edge );
    /* sort the vertex id's */
    sort( &verts[0], &verts[count-1] );
    /* compare each vertex id with that of the next highest */
    for( i = 0 ; i < count-1 ; i++ )
        if( verts[i] == verts[i+1] ) {
            if( duplicate != NULL )
                *duplicate = i;
            is_manifold = 0;
        }
    if( verts != NULL )
        free( verts );

    done:
    UNREFERENCED(status);
    return is_manifold;


} /* end function loop_is_manifold */


/* if we discover that the vertex id's of a loop are not unique, we can call this function
 * resolve the situation. */
static int make_loop_manifold(
    int edge,
    half_edge_array alter *ea,
    vertex alter *v_array, 
    int pcount, 
    int alter *newpcount, 
    mtable_info alter *mtable,
    loop_table alter *ltable,
    int alter *remap ) 
{
    int duplicate;
    half_edge *b, *bad[2];
    int status = STATUS_NORMAL;
    int i, bi;
    int alter *loops = ltable->loops;
    int alter *N = ltable->N;

    UNREFERENCED(mtable);
    UNREFERENCED(loops);

    while ( !loop_is_manifold( ea, edge, 0, &duplicate, ltable ) ) {
        bi = edge;
        i = 0;
        do{
            b = ea->edges + bi;
            if( b->start == duplicate )
                bad[i++] = b;
            bi = N[bi];
        } while( (bi != edge) && (i < 2) );  
        if( i != 2 ) {
            COMPLAIN( "internal error: make_loop_manifold() was expecting a loop w/ duplicated vertex id" );
            status = STATUS_ERROR;
            goto done;
        }

        /* for now we will assume that the N and P values are pointing to the right things and that 
         * the vertex id is all that needs to be fixed. */
        remap[ *newpcount - pcount ] = bad[0]->start;
        remap_vertex( ea, bad[0], bad[0]->start, *newpcount );
        if( v_array != NULL )
            fix_edge_references( v_array, remap[*newpcount-pcount], ea );
        *newpcount += 1;
    }

    done:
    return status;

} /* end function make_loop_manifold */


/* On Rossignac's advice, we fill any holes with dummy triangles
 * and simply record which triangles are dummy.  This avoids CASE_M
 * operations, which we have determined to be unstable.  The normal usage
 * of this function is to keep calling it until each distinct piece has
 * at most one hole (defined as a closed loop of open edges).
 */
static int plug_the_hole( 
    int edge,
    half_edge_array alter *ea,
    vertex alter *v_array, 
    int pcount, 
    int alter *newpcount,
    mtable_info alter *mtable,
    loop_table alter *ltable,
    int *remap )
{
    int i, count, first_new_edge;
    half_edge *b, *b2;
    int bi, bi2;
    int e1, e2, e3;
    int start, end, third;
    int *vertices_on_edge = NULL;
    int new_vertex;
    int status = STATUS_NORMAL;
    int alter *loops = ltable->loops;
    int alter *P = ltable->P;
    int alter *N = ltable->N;
    
    bi = edge;
    count = 0;
    ASSERT( N[bi] != GARBAGE_EDGE );
    ASSERT( validate_edge( ea, ea->edges + edge, NULL ) );
    do{
        bi = N[bi];
        count++;
    } while( bi != edge );

    if( !loop_is_manifold( ea, edge, count, NULL, ltable ) ) {
        if( (status = make_loop_manifold( edge, ea, v_array, pcount, newpcount, mtable, ltable, remap )) != STATUS_NORMAL ) {
            goto done;
        }
    }

    vertices_on_edge = (int *)malloc( count * sizeof( int ) );
    if( vertices_on_edge == NULL ) {
        COMPLAIN( "vertices_on_edge allocation failed in function plug_the_hole" );
        status = STATUS_ERROR;
        goto done;
    }
    bi = edge;
    i = 0;
    do{
        vertices_on_edge[i] = ea->edges[bi].start;
        bi = P[bi];
        i++;
    } while( bi != edge );

    first_new_edge = ea->used;
    new_vertex = *newpcount;
    *newpcount += 1;
    /* reallocate the N and P pointers in the loop table if necessary.  
     * This while loop is expected to almost never execute */
    while( ea->used + (3*count) > ltable->np_allocated ) {
        loop_table_np_expand( ltable );
        P = ltable->P;
        N = ltable->N;
    }
    
    /* add the edges for one new triangle per iteration */
    for( i = 0 ; i < count ; i++ ) {
        start = vertices_on_edge[i];
        end = vertices_on_edge[(i+1)%count];
        third = new_vertex;
        if( ea->used + 3 >= ea->allocated ) {
            if((status = half_edge_array_expand( ea )) <= 0 ) 
                return status;
        }
        HALF_EDGE_INIT( ea->edges + ea->used );
        e1 = ea->used++;
        HALF_EDGE_INIT( ea->edges + ea->used );
        e2 = ea->used++;
        HALF_EDGE_INIT( ea->edges + ea->used );
        e3 = ea->used++;

        /* set up pointers to the vertices of the plug */
        ea->edges[e1].start = start;
        ea->edges[e2].start = end;
        ea->edges[e3].start = third;
        if( v_array != NULL )
            vertex_append_edge( v_array + new_vertex, e3, NULL );
        /* set up N and P pointers (bounding loop) */    
        N[e1] = (i==count-1)?(first_new_edge):(e1+3);
        P[e1] = e1 - 3 + ((i==0)?(count*3):(0));
        /* set up twin pointers */
        ea->edges[e2].twin = (i==count-1)?(first_new_edge + 2):(e2+4);
        ea->edges[e3].twin =  e3 - 4 + ((i==0)?(count*3):(0));
    }
    //we used to do an mtable_info_append_dummy here, but it is no longer needed because we
    // now we do it at a later point based on information from the pointmap.

#ifdef DEBUG
    for( i = first_new_edge ; i < ea->used ; i++ )
        if( (status = validate_edge( ea, ea->edges + i, NULL )) <= 0 )
            goto done;
#endif

    /* find the first matching edges.  This while loop shouldn't need to execute,
     * but is there in case something above in this function changes */
    bi = edge;
    bi2 = P[first_new_edge];
    b = ea->edges + bi;
    b2 = ea->edges + bi2;
    while( ea->edges[bi2].start != ea->edges[N[bi]].start ) {
        bi2 = N[bi2];
    } 
    /* sew the loops together */
    do{
        ea->edges[bi].twin = bi2;
        ea->edges[bi2].twin = bi;
        bi = N[bi];
        bi2 = P[bi2];
    } while( bi != edge );
    
    /* now destroy the loops */
    bi = edge;
    do{
        bi2 = N[bi]; /* save N[bi] before we bash it */
        N[bi] = GARBAGE_EDGE;
        P[bi] = GARBAGE_EDGE;
        loops[ea->edges[bi].start] = 0;
        bi = bi2;
    } while( bi != edge );
    bi = first_new_edge;
    do{
        bi2 = N[bi]; /* save N[bi] before we bash it */
        N[bi] = GARBAGE_EDGE;
        P[bi] = GARBAGE_EDGE;
        bi = bi2;
    } while( bi != first_new_edge );

#ifdef DEBUG
    for( i = first_new_edge ; i < ea->used ; i++ )
        if( (status = validate_edge( ea, ea->edges + i, NULL )) <= 0 )  
            goto done;
#else
    goto done;
#endif

    done:
    if( vertices_on_edge != NULL )
        free( vertices_on_edge );
    return status;

} /* end function plug_the_hole */


static int plug_holes( 
    half_edge_array alter *ea,
    vertex *v_array,
    int pcount, int pcount_max,
    int num_pieces, int const *loops_per_piece, 
    int alter *pieces, 
    int alter *newpcount, 
    mtable_info alter *mtable,
    loop_table alter *ltable,
    int alter *remap )
{
    int status = STATUS_NORMAL;
    int i, num_new_vertices = 0;
    half_edge *e;
    int alter *loops_per_piece_copy;

    /* add 1 to allocation because pieces are 1-based, not 0-based */
    loops_per_piece_copy = (int *) malloc ((num_pieces + 1) * sizeof( int ) );    
    if( loops_per_piece_copy == NULL ) {
        COMPLAIN( "loops_per_piece_copy allocation failed in function plug_holes" );
        status = STATUS_ERROR;
        goto done;
    }
    for( i = 0 ; i < num_pieces + 1 ; i++ )
        loops_per_piece_copy[i] = loops_per_piece[i];

    /* first make sure that we won't overrun the array we've allocated for vertices */    
    for( i = 1 ; i < num_pieces + 1 ; i++ ) {
        if( loops_per_piece[i] > 1 )
            num_new_vertices += loops_per_piece[i] - 1;
    }
    if( *newpcount + num_new_vertices > pcount_max )
        return 0;

    for( i = 0 ; i < ea->used ; i++ ) {
        e = ea->edges + i;
        /* bounds check the value of pieces[ e->start ] */
        ASSERT( (pieces[ e->start ] >= 0) && (pieces[ e->start ] <= num_pieces) );
        if( ( !EDGE_INVALID(ltable->N[i]) ) &&
            ( loops_per_piece_copy[ pieces[ e->start ] ] > 1 ) ) {
                loops_per_piece_copy[ pieces[ e->start ] ] -= 1;
                remap[ *newpcount - pcount ] = DUMMY_VERTEX;
                plug_the_hole( i, ea, v_array, pcount, newpcount, mtable, ltable, remap );
        }
    }

    done:
    if( loops_per_piece_copy != NULL )
        free( loops_per_piece_copy );
    return status;

} /* end function plug_holes */


#ifdef DEBUG
/* validate_loops
 * debugging function to enforce the assumptions about the loops
 */
static int validate_loops( half_edge_array const *ea, loop_table const *ltable, int pcount )
{
    int status = STATUS_NORMAL;
    int i;
    int *loops = ltable->loops;
    int *N = ltable->N;
    char *refs;
    int v;

    refs = (char *) malloc( pcount * sizeof( char ) );
    memset( refs, 0, pcount * sizeof( char ) );
    /* we should not have more than one valid N edge starting at vertex i */
    for( i = 0 ; i < ea->used ; i++ ) {
        if( !EDGE_INVALID( N[i] ) ) {
            v = ea->edges[N[i]].start;
            if( VERTEX_SPECIAL(v) ) {
                ASSERT( v != GARBAGE_VERTEX );
                v = EA_VERTEX_INDEX(v);
            }
            ASSERT( v >= 0 && v < pcount );
            ASSERT( refs[v] == 0 );
            refs[v]++;
        }
    }
    /* every vertex i should have a non-zero loop id if and only if it 
     * is referenced by a valid N edge */
    for( i = 0 ; i < pcount ; i++ ) {
        if( loops[i] != 0 ) {
            ASSERT( refs[i] == 1 );
        }
        else {
            ASSERT( refs[i] == 0 );
        }
    }
    LABEL(done:);
    free( refs );
    return status;
}

#endif


/* normally, when we plug holes, we leave one hole per piece as the initial bounding
 * loop.  Do do otherwise is usually an unnecessary expense, because a split is
 * introduced in any watertight surface.  If and when we discover a handle, though,
 * we plug all the holes so that we make sure not to have to use any (unstable)
 * CASE_M ops for the holes introduced by handle tearing */
static int plug_all_holes( 
    half_edge_array alter *ea,
    vertex *v_array,
    int pcount, int pcount_max,
    int alter *newpcount, 
    mtable_info alter *mtable,
    loop_table alter *ltable,
    int alter *remap )
{
    int status = STATUS_NORMAL;
    int i;
    half_edge *e;

    for( i = 0 ; i < ea->used ; i++ ) {
        e = ea->edges + i;
        if( !EDGE_INVALID( ltable->N[i] ) ) {
            if( *newpcount >= pcount_max ) {
                status = STATUS_ERROR;
                goto done;
            }
            remap[ *newpcount - pcount ] = GARBAGE_VERTEX;
            plug_the_hole( i, ea, v_array, pcount, newpcount, mtable, ltable, remap );
        }
    }

    done:
    #ifdef DEBUG
        for( i = 0 ; i < ea->used ; i++ ) {
            validate_edge( ea, ea->edges + i, ltable );
            /* every open edge should be part of a bounding loop */
            if( EDGE_INVALID( ea->edges[i].twin ) ) {
                ASSERT( !EDGE_INVALID( ltable->N[i] ) );
            }
        }
        ASSERT( validate_loops(ea, ltable, *newpcount) );
    #endif
    return status;

} /* end function plug_all_holes */


/* this function is a little different from most implementations of roughly
 * the same thing, simply because we reserve 0 as an indicator of "no loop" */
static int expand_loops_edges( loop_table alter *ltable )
{
    int *temp;

    if( ltable->loops_edges_allocated < 10 )
        ltable->loops_edges_allocated = 10;
    else
        ltable->loops_edges_allocated *= 2;
    temp = (int *) malloc ( (2 + ltable->loops_edges_allocated) * sizeof( int ) );
    if( !temp )
        return STATUS_ERROR;
    if( ltable->loops_edges ) {
        memcpy( temp, ltable->loops_edges, (1 + ltable->loops_used) * sizeof( int ) );
        free( ltable->loops_edges );
    }
    ltable->loops_edges = temp;
    /* make sure that loop id 0 can never be used */
    temp[0] = GARBAGE_EDGE;
    return STATUS_NORMAL;
}



/* create_loops
 * finds all of the open edges (the half edges with invalid twins) and follows them
 * to create closed loops. 
 * returns success/failure */
static int create_loops( 
    vertex alter *v_array, half_edge_array const *ea, int pcount, int pcount_max,   /* input */
    int alter *newpcount_in_out, loop_table alter *ltable, int alter *remap )       /* output */
{
    int i, ai, bi;
    half_edge *a, *b;       /* a walks the entire loop, b walks around the current vertex to find the next link */
    int newpcount = *newpcount_in_out;
    int *edge_loop_id;
    int status = STATUS_NORMAL;     /* assume success until we hear otherwise */

    ltable->loops_used = 0;
    memset( ltable->P, 0x80, ltable->np_allocated * sizeof( int ) );
    memset( ltable->N, 0x80, ltable->np_allocated * sizeof( int ) );
    /* For most purposes, it is enough to associate loop id's with vertices.
     * However, in this case, we need to be prepared for backwards faces.
     * A backwards face claims the same vertices as an edge as the opening that
     * it fills, leaving us with nothing to recognize the fact that there is a new
     * loop that we need to follow and set N and P pointers for. */
    edge_loop_id = (int *) malloc ( ea->used * sizeof( int ) );
    if( edge_loop_id == NULL ) {
        COMPLAIN("edge_loop_id allocation failed in function create_loops()" );
        status = STATUS_ERROR;
        goto done;
    }
    memset( edge_loop_id, 0, ea->used * sizeof( int ) );
    for( i = 0 ; i < ea->used ; i++ ) {
        if( EDGE_INVALID( ea->edges[i].twin ) &&
            !edge_loop_id[i] ) {
            /* we've found a new loop. Walk around the whole thing */
            a = ea->edges + i;
            do {
                ai = (int)(a - ea->edges);
                if( ltable->loops[ a->start ] != 0 ) {
                    /* another loop has already claimed this vertex.
                     * we should only get here if there is a problem with the 
                     * surface (non-manifold) that needs fixing */
                    if( newpcount >= pcount_max ) {
                        COMPLAIN( "too many non-manifolds" );
                        status = STATUS_ERROR;
                        goto done;
                    }
                    remap[ newpcount - pcount ] = a->start;
                    remap_vertex( ea, a, a->start, newpcount );
                    if( v_array != NULL )
                        fix_edge_references( v_array, remap[newpcount-pcount], ea );
                    newpcount++;
                }
                ltable->loops[ a->start ] = ltable->loops_used+1;
                edge_loop_id[ ai ] = ltable->loops_used+1;
                /* bi walks around a particular vertex to find the next link */
                bi = HNEXT(ai);
                while( !EDGE_INVALID( ea->edges[bi].twin ) ) {
                    bi = ea->edges[bi].twin;
                    bi = HNEXT(bi);
                }
                b = ea->edges + bi;
                ltable->N[ai] = (int)(b - ea->edges);
                ltable->P[bi] = (int)(a - ea->edges);
                ai = ltable->N[ai];
                a = ea->edges + ai; 
            } while ( ai != i );
            if( ltable->loops_used >= ltable->loops_edges_allocated - 1 ) {
                status = expand_loops_edges( ltable );
            }
	    /* note: loops are 1-based, since zero is reserved as a special indicator for "no loop".
	     * increment loops_used before set to account for that. */
            ltable->loops_used++;
            ltable->loops_edges[ ltable->loops_used ] = i;
        }
    }
    if( newpcount_in_out != NULL )
        *newpcount_in_out = newpcount;


#ifdef DEBUG
    for( i = 0 ; i < ea->used ; i++ ) {
        validate_edge( ea, ea->edges + i, ltable );
        /* every open edge should be part of a bounding loop */
        if( EDGE_INVALID( ea->edges[i].twin ) ) {
            ASSERT( !EDGE_INVALID( ltable->N[i] ) );
        }
    }
    ASSERT( validate_loops(ea, ltable, newpcount) );
#endif
    done:
    if( edge_loop_id != NULL )
        free( edge_loop_id );
    return status;

} /* end function create_loops */




/* An alternative version of connect_twins (see below) that kicks in if and when we find 
 * more than two edges referencing the same pair of vertices.  In this version of the function,
 * we take the extra precautions required when such a situation occurs.  */
static int connect_twins_hard(
    vertex alter *v_array, half_edge_array const *ea, 
    int pcount, int pcount_max, 
    int alter *newpcount_in_out, int alter *remap )
{
    int status = STATUS_NORMAL;
    vertex *v, *v2;
    int i, j, k, ei, end, ei2, ei3, end2, bi, twin, maxi, add_v;
    int newpcount = *newpcount_in_out;
    VArray<int> multiple_edges;

    UNREFERENCED(pcount);
    UNREFERENCED(remap);

    for( i = 0 ; i < pcount_max ; i++ ) {
        v = v_array + i;
        for( j = 0 ; j < v->e_used ; j++ ) {
            ei = v->edges[j];
            end = ea->edges[HNEXT(ei)].start;
            /* comparing edges{v} to edges{v2}. Connect the half-edges to their twins */
            if( EDGE_INVALID( ea->edges[ei].twin ) ) {
                v2 = &v_array[end];
                for( k = 0 ; k < v2->e_used ; k++ ) {
                    ei2 = v2->edges[k];
                    end2 = ea->edges[HNEXT(ei2)].start;
                    if( ea->edges[ei2].start == end && end2 == ea->edges[ei].start ) {
                        if( ea->edges[ei2].twin == GARBAGE_EDGE ) {
                            ea->edges[ei].twin = ei2;
                            ea->edges[ei2].twin = ei;
                        }
                        else if( ea->edges[ei2].twin == MULTIPLE_EDGE ) {
                            //attempt to connect to a previously known multiple_edge.
                            //just the new guy needs to be marked.
                            ea->edges[ei].twin = MULTIPLE_EDGE;                          
                            multiple_edges.Append( ei );
                        }
                        else {
                            //discovered a new multiple_edge.  break apart the previously
                            //existing pair and append all three of them to the list.
                            ASSERT( !EDGE_INVALID(ei2) );
                            ei3 = ea->edges[ei2].twin;
                            ASSERT( !EDGE_INVALID(ei3) );
                            ea->edges[ei].twin = MULTIPLE_EDGE;                          
                            ea->edges[ei2].twin = MULTIPLE_EDGE;                          
                            ea->edges[ei3].twin = MULTIPLE_EDGE;                          
                            multiple_edges.Append( ei );
                            multiple_edges.Append( ei2 );
                            multiple_edges.Append( ei3 );
                        }
                        break; /* goto next_j */
                    }
                }
                /* next_j */
            }
        }
    }

    /* We know that separating out the triangles marked as multiple is going
     * to cause remappings later on (see create_loops()), so we might as well 
     * punt if they would be enough to put us over the top. */
    add_v = 3 * multiple_edges.Count();
    if( *newpcount_in_out + add_v > pcount_max )
        status = STATUS_ERROR;

    /* Any triangle that has an edge marked as multiple will be sent as a singleton.
     * By severing it from its twins, it will be treated roughly the same as if it were
     * a backwards face. */
    maxi = multiple_edges.Count();
    for( i = 0 ; i < maxi ; i++ ) {
        ei = multiple_edges[i];
        bi = HNEXT(ei);
        if( ea->edges[bi].twin >= 0 ) {
            twin = ea->edges[bi].twin;
            INVALIDATE_EDGE( ea->edges[twin].twin );
            INVALIDATE_EDGE( ea->edges[bi].twin );
        }
        bi = HPREV(ei);
        if( ea->edges[bi].twin >= 0 ) {
            twin = ea->edges[bi].twin;
            INVALIDATE_EDGE( ea->edges[twin].twin );
            INVALIDATE_EDGE( ea->edges[bi].twin );
        }
    }

  LABEL(done:);
    *newpcount_in_out = newpcount;
    return status;

} /* end function connect_twins_hard */


static int connect_twins(
    vertex alter *v_array, half_edge_array const *ea, 
    int pcount, int pcount_max, 
    int alter *newpcount_in_out, int alter *remap )
{
    int status = STATUS_NORMAL;
    vertex *v, *v2;
    int i, j, k, ei, end, ei2, end2;
    half_edge *e, *e2;
    int newpcount = *newpcount_in_out;

    UNREFERENCED(remap); UNREFERENCED(pcount);

    for( i = 0 ; i < pcount_max ; i++ ) {
        v = v_array + i;
        for( j = 0 ; j < v->e_used ; j++ ) {
            /* comparing edges{v} to edges{v2}. Connect the half-edges to their twins */
            if( EDGE_INVALID( ea->edges[v->edges[j]].twin )  ) {
                ei = v->edges[j];
                e = ea->edges + ei;
                end = ea->edges[HNEXT(ei)].start;
                v2 = v_array + end;
                for( k = 0 ; k < v2->e_used ; k++ ) {
                    ei2 = v2->edges[k];
                    e2 = ea->edges + ei2;
                    end2 = ea->edges[HNEXT(ei2)].start;
                    if( e2->start == end && end2 == e->start ) {
                        if( EDGE_INVALID( e2->twin ) ) {
                            /* twins should reference vertices in opposite order and point to each other */
                            e->twin = (int)(e2 - ea->edges);
                            e2->twin = (int)(e - ea->edges);
                            break; /* goto next_j */
                        }
                        else {
                            status = STATUS_TRY_AGAIN;
                            goto done;
                        }
                    }
                }
                /* next_j */
            }
        }
    }

    done:
    *newpcount_in_out = newpcount;
    return status;

} /* end function connect_twins */


static int remove_nonmanifolds(
    vertex alter *v_array, half_edge_array const *ea, 
    int pcount, int pcount_max, 
    int alter *newpcount_in_out, int alter *remap )
{
    int status = STATUS_NORMAL;
    vertex *v;
    int i, bi;
    half_edge *h;
    int newpcount = *newpcount_in_out;
    int count = 0;

    UNREFERENCED(remap); UNREFERENCED(pcount_max); UNREFERENCED(pcount);

    for( i = 0 ; i < newpcount ; i++ ) {
        v = v_array + i;
        if( v->edges == NULL || v->e_used == 0 ) continue;
        do {
            h = ea->edges + v->edges[0];
            count = 0;
            
            /* circle the vertex to the left */
            bi = v->edges[0];
            while( !EDGE_INVALID( ea->edges[bi].twin ) ) {
                count++;
                bi = ea->edges[bi].twin;
                bi = HNEXT(bi);
                if( bi == v->edges[0] ) 
                    break;
            }
            /* if not back where we started, circle to the right */
            if( EDGE_INVALID( ea->edges[bi].twin ) ) {
                bi = v->edges[0];
                bi = HPREV(bi);
                while( !EDGE_INVALID( ea->edges[bi].twin ) ) {
                    count++;
                    bi = ea->edges[bi].twin;
                    bi = HPREV(bi);
                } 
                count++;
            }
            if( count > v->e_used ) {
                /* this should never happen */
                COMPLAIN( "internal error" );
                return STATUS_ERROR; 
            }
            if( count != v->e_used ) {
                /* there are too many unknowns involved when we hit this situation.  We have to just punt. */
                #if 0
                    if( newpcount + 1 >= pcount_max ) {
                        COMPLAIN( "remove_nonmanifolds() found too many nonmanifolds" );
                        status = STATUS_ERROR;
                        goto done;
                    }
                    remap[ newpcount - pcount ] = h->start;
                    remap_vertex( ea, h, h->start, newpcount );
                    newpcount++;
                    fix_edge_references( v_array, i, ea );
                #endif
                return STATUS_ERROR;
            }
        } while( count != v->e_used );
        ASSERT( count == v->e_used );
    }
    *newpcount_in_out = newpcount;
    LABEL(done:);
    return status;

} /* end function remove_nonmanifolds */


#ifdef DEBUG
/* validate_edge_references
 * For every vertex {i}, every edge {j} that it contains should start with i.
 * This function is for debugging only. */
static int validate_edge_references( vertex const *v_array, half_edge_array const *ea, int len )
{
    int status = STATUS_NORMAL;
    int i, j;

    for( i = 0 ; i < len ; i++ ) {
        for( j = 0 ; j < v_array[i].e_used ; j++ ) {
            if( ea->edges[v_array[i].edges[j]].start != i ) {
                ASSERT( ea->edges[v_array[i].edges[j]].start == i );
                return 0;
            }
        }
    }
    LABEL(done:);
    return status;
} /* end function validate_edge_references */
#endif




static int sufficient_shared( vertex *v_array, int pcount )
{
    int i;
    int shared_count = 0;

    for( i = 0 ; i < pcount ; i++ ) {
        if( v_array[i].e_used > 1 )
            shared_count++;
    }
    return (shared_count > pcount * 0.2f);
}

/* half_edge_array_convert
 * takes a HOOPS style indexed face set and converts it into the form of an array of half edges.
 */
static int half_edge_array_convert( 
    int pcount, int pcount_max, int faces_len, int const *flist, bool by_tristrips,            /* input */
    half_edge_array alter *ea, mtable_info *mtable, int hints,
    int alter *newpcount_out, loop_table alter *ltable, int alter *remap, vhash_t alter **tristrip_hash_out )  /* output */
{
    vertex *v_array = NULL;
    int i;
    int const *ptr = NULL;  /* points to the current face */
    int const *end;
    int hi1, hi2, hi3;
    int newpcount = pcount;
    int *pieces = NULL;
    int num_pieces; /* records the number of topologically distinct parts of the model */
    int status = STATUS_NORMAL;
    int *loops_per_piece = NULL;
    vhash_t *tristrip_hash = NULL;
    bool reverse;
    int strip_len;
    int mate; //the edge id from the previous triangle to connect to (if i > 1)

    /* create our reverse lookup table */
    v_array = (vertex *) malloc (pcount_max * sizeof( vertex ));
    if( v_array == NULL ) {
        COMPLAIN( "vertex array allocation failed" );
        status = STATUS_ERROR;
        goto done;
    }
    for( i = 0 ; i < pcount_max ; i++ ) {
        v_array[i].edges = NULL;
        v_array[i].e_used = 0;
    }

    ptr = flist;
    end = flist + faces_len;
    if( !by_tristrips ) {
        while( ptr < end ) {
            /* since we're not by tristrips here, any face list that contained non-triangular
             * flist should have been converted prior to this function */
            ASSERT( ptr[0] == 3 );
            /* don't consider degenerate flist */
            if( ptr[1] != ptr[2] &&
                ptr[2] != ptr[3] &&
                ptr[3] != ptr[1] ) {
				if( ea->used + 3 >= ea->allocated ) {
					if((status = half_edge_array_expand( ea )) <= 0 ) 
						return status;
				}
				HALF_EDGE_INIT( ea->edges + ea->used );
				hi1 = ea->used++;
				HALF_EDGE_INIT( ea->edges + ea->used );
				hi2 = ea->used++;
				HALF_EDGE_INIT( ea->edges + ea->used );
				hi3 = ea->used++;
				ea->edges[hi1].start = ptr[1];
				ea->edges[hi2].start = ptr[2];
				ea->edges[hi3].start = ptr[3];
				/* append to the vertex at which the edges start */
				vertex_append_edge( v_array + ptr[1], hi1, NULL );
				vertex_append_edge( v_array + ptr[2], hi2, NULL );
				vertex_append_edge( v_array + ptr[3], hi3, NULL );
			}
			ptr += 4;
        }
    }
    else {
        tristrip_hash = new_vhash( 100, malloc, free );
        while( ptr < end ) {
            vhash_insert_item( tristrip_hash, I2V(ea->used), (void *)ptr );
            ASSERT( *ptr > 0 ); //xxx need to add support for trifans
            strip_len = *ptr;
            reverse = false;
            // create individual triangles out of the triangle strips 
            for( i = 0 ; i < strip_len-2 ; i++ ) {
                if( ea->used + 3 >= ea->allocated ) {
                    if((status = half_edge_array_expand( ea )) <= 0 ) 
                        return status;
                }
                HALF_EDGE_INIT( ea->edges + ea->used );
                hi1 = ea->used++;
                HALF_EDGE_INIT( ea->edges + ea->used );
                hi2 = ea->used++;
                HALF_EDGE_INIT( ea->edges + ea->used );
                hi3 = ea->used++;
                ASSERT( (ea->used % 3) == 0 );
                if( reverse ) {
                    ea->edges[hi1].start = ptr[i+2];
                    ea->edges[hi2].start = ptr[i+1];
                    mate = ea->used - 5; 
                }
                else {
                    ea->edges[hi1].start = ptr[i+1];
                    ea->edges[hi2].start = ptr[i+2];
                    mate = ea->used - 4;
                }
                ea->edges[hi3].start = ptr[i+3];
                // append to the vertex at which the edges start 
                vertex_append_edge( v_array + ea->edges[hi1].start, hi1, NULL );
                vertex_append_edge( v_array + ea->edges[hi2].start, hi2, NULL );
                vertex_append_edge( v_array + ea->edges[hi3].start, hi3, NULL );           
                if( i > 1 ) {
                    //interior edges within a tristrip can be prematched so that 
                    //  we save some time at connect_twins
//                    ASSERT( ea->edges[ ea->used-3 ].start == ea->edges[ HNEXT(mate) ].start );
//                    ASSERT( ea->edges[ mate ].start == ea->edges[ HNEXT(ea->used-3) ].start );
//                    ea->edges[ ea->used-3 ].twin = mate;
//                    ea->edges[ mate ].twin = ea->used-3;
                }
                reverse = !reverse;
            }
            ptr += strip_len + 1;
        }
    }

    if( !sufficient_shared( v_array, pcount_max ) ) {
        status = STATUS_ERROR;
        goto done;
    }

    status = connect_twins( 
            v_array, ea, pcount, pcount_max, &newpcount, remap );
    if( status == STATUS_TRY_AGAIN ) {
        //non-manifold edges found.  not possible to use tristrips.
        by_tristrips = false;
        status = connect_twins_hard( 
                v_array, ea, pcount, pcount_max, &newpcount, remap );
    }
    if( status <= 0 ) {
        COMPLAIN( "error reported from connect_twins\n" );
        goto done; 
    }
    ASSERT( validate_edge_references( v_array, ea, newpcount ) );

    /* allow for hole plugging to expand ea by up to a small factor.  If it exceeds 
     * that factor, ltable->N and ltable->P will be reallocated and copied */
    if( (status = loop_table_init( ltable, pcount_max, (int)(1.2 * ea->used) )) == STATUS_ERROR ) {
        COMPLAIN( "loop table initialization failed\n" );
        status = STATUS_ERROR;
        goto done;
    }

    if((status = create_loops( 
            v_array, ea, pcount, pcount_max,               /* input */
            &newpcount, ltable, remap                      /* output */
        )) <= 0 )
        goto done;
    ASSERT( validate_edge_references( v_array, ea, newpcount ) );

    if( !(hints & HINT_MANIFOLD) ) {
        if((status = remove_nonmanifolds( 
                v_array, ea, pcount, pcount_max, &newpcount, remap
            )) <= 0 )
            goto done;    
        ASSERT( validate_edge_references( v_array, ea, newpcount ) );
    }

    pieces = (int *) malloc ( pcount_max * sizeof( int ) );
    loops_per_piece = (int *) malloc ( (newpcount+1) * sizeof( int ) );  /* an extremely loose upper bound (assumes every vertex is its own piece) */
    if( pieces == NULL || loops_per_piece == NULL ) {
        COMPLAIN( "pieces or loops_per_piece array allocation failed" );
        status = STATUS_ERROR;
        goto done;
    }
    memset( pieces, 0, pcount_max * sizeof( int ) );
    memset( loops_per_piece, 0, newpcount * sizeof( int ) );

    if((status = find_pieces( 
            ea, newpcount, v_array, ltable->loops,                  /* input */
            pieces, &num_pieces, loops_per_piece                    /* output */
        )) <= 0 )
        goto done;

    if((status = plug_holes( 
            ea, v_array, pcount, pcount_max,                        /* input */
            num_pieces, loops_per_piece, pieces,                    /* input */
            &newpcount, mtable, ltable, remap                       /* output */
        )) <= 0 )
        goto done;

    #ifdef DEBUG
        for( i = 0 ; i < ea->used ; i++ ) {
            if( EDGE_INVALID( ea->edges[i].twin ) ) {
                ASSERT( !EDGE_INVALID( ltable->N[i] ) );
                ASSERT( ltable->loops[ ea->edges[i].start ] != 0 );
            }
            validate_edge( ea, ea->edges + i, ltable );
        }
    #endif

  done:
    *tristrip_hash_out = tristrip_hash;
    if( tristrip_hash && !by_tristrips ) {
        //we attempted to use tristrip info, but ran into a problem.
        delete_vhash( tristrip_hash );
        *tristrip_hash_out = NULL;
    }

    /* clean up all temporary structures.  
     * We are left with the half_edge_array, to be cleaned up later. */
    if( v_array != NULL ) {
        for( i = 0 ; i < pcount_max ; i++ )
            if( v_array[i].edges != NULL )
                vertex_free( v_array + i );
        free( v_array );
    }
    if( pieces != NULL )
        free( pieces );
    if( loops_per_piece != NULL )
        free( loops_per_piece );
    *newpcount_out = newpcount;
    return status;

} /* end function half_edge_array_convert */


/* XXX tjh: seems to me that only the 1st and 3rd cases are necessary.  Not sure of
 * that, though, so I'll leave it as is for now */
static int neighborhood_search_for_open( half_edge_array const *ea, int edge )
{
    int bi, bi2;

    bi = bi2 = edge;
    do {
        if( EDGE_INVALID( ea->edges[bi2].twin ) )
            return bi2;
        bi2 = ea->edges[bi2].twin;
        bi2 = HNEXT(bi2);
    } while (bi2 != bi);

    bi = bi2 = edge;
    do {
        if( EDGE_INVALID( ea->edges[bi2].twin ) )
            return bi2;
        bi2 = ea->edges[bi2].twin;
        bi2 = HPREV(bi2);
    } while (bi2 != bi);

    bi = bi2 = HNEXT(edge);
    do {
        if( EDGE_INVALID( ea->edges[bi2].twin ) )
            return bi2;
        bi2 = ea->edges[bi2].twin;
        bi2 = HNEXT(bi2);
    } while (bi2 != bi);

    bi = bi2 = HNEXT(edge);
    do {
        if( EDGE_INVALID( ea->edges[bi2].twin ) )
            return bi2;
        bi2 = ea->edges[bi2].twin;
        bi2 = HPREV(bi2);
    } while (bi2 != bi);
    return GARBAGE_EDGE;
}



/* create_start
 * Couldn't find a loop, so we fake it by creating a small split
 * Note that we step 3 per iteration.  Triangles have consecutive
 * edges, all of which will be touched when used. */
static int create_start( 
        half_edge_array const *ea, 
        int index, 
        char const *touched, 
        int pcount, 
        int pcount_max,
        int alter *newpcount_in_out, 
        loop_table alter *ltable, 
        int alter *pointmap, 
        int alter *remap )
{
    int one, two, three, four;
    int status = STATUS_NORMAL;
    int *P = ltable->P;
    int *N = ltable->N;

    UNREFERENCED(touched);
    UNREFERENCED(pointmap);

    ASSERT( touched[index] == 0 );
    if( *newpcount_in_out >= pcount_max )
        return STATUS_ERROR;
    one = index;
    two = HNEXT(one);
    three = ea->edges[two].twin;
    four = ea->edges[one].twin;
    //if one of the involved vertices is on a loop, we shouldn't be here.
    if( ltable->loops[ ea->edges[one].start ] ||
        ltable->loops[ ea->edges[two].start ] ||
        ltable->loops[ ea->edges[three].start ] )
        return STATUS_ERROR;
    N[one] = two;
    N[two] = three;
    N[three] = four;
    N[four] = one;
    P[one] = four;
    P[two] = one;
    P[three] = two;
    P[four] = three;
    INVALIDATE_EDGE( ea->edges[one].twin );
    INVALIDATE_EDGE( ea->edges[two].twin );
    INVALIDATE_EDGE( ea->edges[three].twin );
    INVALIDATE_EDGE( ea->edges[four].twin );
    remap[ *newpcount_in_out - pcount ] = ea->edges[two].start;
    remap_vertex( ea, ea->edges + two, ea->edges[two].start, *newpcount_in_out );
    ASSERT( ltable->loops[ ea->edges[one].start ] == 0 );
    ASSERT( ltable->loops[ ea->edges[four].start ] == 0 );
    ASSERT( ltable->loops[ *newpcount_in_out ] == 0 );
    if( ltable->loops_used >= ltable->loops_edges_allocated - 1 )
        status = expand_loops_edges( ltable );
    ltable->loops_used++;
    ltable->loops_edges[ ltable->loops_used ] = one;
    ltable->loops[ ea->edges[one].start ] = ltable->loops_used;
    ltable->loops[ ea->edges[two].start ] = ltable->loops_used;
    ltable->loops[ ea->edges[three].start ] = ltable->loops_used;
    ltable->loops[ ea->edges[four].start ] = ltable->loops_used; /* technically not necessary since two.start == four.start */
    ltable->loops[ *newpcount_in_out ] = ltable->loops_used;
    *newpcount_in_out += 1;
    LABEL(done:);
    return status;

} /* end function create_start */



/* find_start
 * returns the index of an edge that can serve as a good starting point.
 * May introduce a fake seam in the surface if no open edges are immediately found */
static int find_start( half_edge_array alter *ea, int alter *place_in_out, char const *touched, 
        int pcount, int pcount_max, int alter *newpcount_in_out, 
        loop_table alter *ltable, int alter *pointmap, int alter *remap )
{
    int i, open, index, edge;

    /* look for the first untouched edge */
      /* default to where we left off last time. */
    index = *place_in_out; 
      /* look to see if anything was left untouched in in loops_edges */
    for( i = 1 ; i <= ltable->loops_used ; i++ ) {
        edge = ltable->loops_edges[i];
        if( EDGE_INVALID( edge ) )
            continue;
        if( !touched[ edge ] && EDGE_INVALID( ea->edges[ edge ].twin ) ) {
            /* set the starting point to be the untouched edge.  We'll hit
             * it in the very first iteration of the next loop */
            index = ltable->loops_edges[i];
            break;
        }
    }
      /* start a linear walk through all edges.  We're not done until we manage to make it all the way through. */
    for( i = 0; i < ea->used ; i++ ) {
        if( !touched[index] ) {
            /* find a loop in the neighborhood if we can.  Otherwise introduce a seam */
            if( EDGE_INVALID( ea->edges[index].twin )) {
                *place_in_out = index; 
                return STATUS_NORMAL;
            }
            else if( !EDGE_INVALID( open = neighborhood_search_for_open(ea,index)) ) {
                *place_in_out = open; 
                //if index is not touched, it should not be possible to have a neighbor that is
                if( touched[open] )
                    return STATUS_ERROR;
                return STATUS_NORMAL;
            }
            else {
                *place_in_out = index;
                return create_start( ea, index, touched, pcount, pcount_max, newpcount_in_out, ltable, pointmap, remap );
            }
        }
        index++;
        if( index == ea->used )
            index = 0;
    }
    return STATUS_COMPLETE;

} /* end function find_start */



/* walk around "third" until we find the other edge from the loop
 * going in.  Used to help process CASE_S and CASE_M2 */
static int find_loop_edge( 
        half_edge_array const *ea, 
        half_edge const *h,
        loop_table const *ltable, 
        char const *touched, 
        half_edge alter **out )
{
    int status = STATUS_NORMAL;
    int bi, hi;
    int const *N = ltable->N;

    hi = bi = (int)(h - ea->edges);
    do {
        bi = ea->edges[bi].twin;
        bi = HPREV(bi);
    } while( EDGE_INVALID( N[bi] ) || bi == hi );
    ASSERT( !EDGE_INVALID( ltable->N[bi] ) );
    ASSERT( !EDGE_INVALID( ltable->P[bi] ) );
    *out = ea->edges + bi;
    UNREFERENCED( touched );
    LABEL(done:);
    return status;      

} /* end function find_loop_edge */


static int is_on_loop( 
        half_edge_array const *ea, 
        int gi,
        loop_table const *ltable,
        int id )
{
    int bi;
    int *N = ltable->N;  

    bi = gi;
    do {
        if( ea->edges[bi].start == id )
            return 1;
        bi = N[bi];
    } while ( bi != gi );
    return 0;

} /* end function is_on_loop */


/* split the half edge array at the currently active loop. 
 * After this function, some of the normal assumptions (such as P[N[i]]==i)
 * might no longer be valid, but that's ok, since the caller will 
 * set STATUS_TRY_AGAIN.  */
static int tear(  
        int gi, 
        half_edge_array alter *ea, 
        int pcount, 
        int alter *newpcount, 
        int pcount_max,
        mtable_info alter *mtable, 
        loop_table alter *ltable,
        int alter *remap ) 
{
    int status = STATUS_NORMAL;
    half_edge *b;
    int i, bi;
    int alter *loops = ltable->loops;
    int alter *N = ltable->N;

    ASSERT( validate_edge( ea, ea->edges + gi, ltable ) );

    /* We are not yet able to handle the case where a handle's tear
     * crosses a dummy.  For now, just punt.  We can think about a more
     * correct solution later. */
    bi = gi;
    do{
        if( ea->edges[bi].start >= pcount ) {
            for( i = 0 ; i < mtable->dummies_used ; i++ ) {
                if( mtable->dummies[i] == ea->edges[bi].start ) {
                    status = STATUS_ERROR;
                    goto done;
                }
            }
        }    
        bi = N[bi];
    } while( bi != gi);

    /* first divorce the loops from their twins */
    bi = gi;
    do{
        b = ea->edges + bi;
        if( !EDGE_INVALID( b->twin ) ) {
            INVALIDATE_EDGE( ea->edges[b->twin].twin );
            INVALIDATE_EDGE( b->twin );
        }    
        bi = N[bi];
    } while( bi != gi );

    /* remap the vertices on the main loop so that it is distinct 
     * from its twin loop */
    bi = gi;
    do{
        remap[ *newpcount - pcount ] = ea->edges[bi].start;
        remap_vertex( ea, ea->edges + bi, ea->edges[bi].start, *newpcount );
        *newpcount += 1;
        if( *newpcount >= pcount_max ) {
            status = STATUS_ERROR;
            goto done;
        }
        bi = N[bi];
    } while( bi != gi );

    done:
    UNREFERENCED(loops);
    return status;

} /* end function tear */


/* compute_opcodes
 * Use a series of opcodes to describe connectivity. The opcodes are:
 *  C: introduce a new vertex (next vertex is off boundary)
 *  L: next vertex is on the boundary to the left
 *  E: dead end (next vertex is on left AND right)
 *  R: next vertex is on the boundary to the right
 *  S: next vertex is elsewhere on the boundary (split boundary into two)
 *  M: next vertex is on a different loop (merge the two loops and introduce new vertices)
 *  M2: different loop was left branch of CASE_S.  Result of a handle.
 * Returns 1 on success, 0 on failure */
static int compute_opcodes( 
        half_edge_array alter *ea, 
		int hints,
        int pcount, 
        int pcount_max,
        int *newpcount_in_out,      
        int alter *opslen, 
        char alter *ops, 
        loop_table alter *ltable, 
        int alter *pointmap, 
        int alter *remap,    
        mtable_info alter *mtable, 
        int alter *associations, 
        int alter *referenced_pcount_out )
{
    int index = 0;
    int used = 0;
    int v=0;
    int j;
    int bi, bi2, gi, gi_next, gi_prev, gi_start, gi_end, gi_third;
    half_edge *gate, *h, *h2, *b, *b2;
    int_stack stack;
    char *touched = NULL;
    /* use negative numbers (guaranteed to be distinct) to identify loops created by S operations */
    int sloop = -1; 
    int active_loop;
    int status = STATUS_NORMAL;
    int has_handles = 0;
    int s_ops;
    int *loops = ltable->loops;
    int *P = ltable->P;
    int *N = ltable->N;
    int newpcount = *newpcount_in_out;
    
    stack.data = NULL;
    touched = (char *) malloc ( ea->used * sizeof( char ) );
    if( touched == NULL ) {
        COMPLAIN( "touched flags allocation failed" );
        status = STATUS_ERROR;
        goto done;
    }
    memset( touched, 0, ea->used * sizeof( char ) );
    ea->visitations_used = 0;
    for(;;) {

        /* the first order of business is to find a starting point */
        status = find_start( ea, &index, touched,  pcount, pcount_max, /* input */
                             &newpcount, ltable, pointmap, remap );     /* output */
        if( status == STATUS_COMPLETE || status == STATUS_ERROR )
            goto done;


        gate = ea->edges + index;
        gi = index;
        b = gate; 
        j = 0;
        bi = gi;
        /* declare the ordering of points for the points that lie on the outside of the loop */
        do {
            if( associations != NULL ) {
                if( bi != gi )
                    associations[0] = ea->edges[ P[bi] ].start;
                else
                    associations[0] = GARBAGE_VERTEX;
                associations[1] = GARBAGE_VERTEX;
                associations[2] = GARBAGE_VERTEX;
                associations += 3;
            }
            pointmap[ v++ ] = ea->edges[bi].start;
            bi = N[bi];
            j++;
        } while( bi != gi );

        /* Now that we have found our starting point, we proceed with encoding 
         * the current region of the surface */
        int_stack_init( &stack );
        active_loop = loops[ gate->start ];
        while( stack.used >= 0 ) {

            gi = (int)(gate - ea->edges);               /* edge */
            gi_prev = HPREV(gi);                        /* edge */
            gi_next = HNEXT(gi);                        /* edge */
            gi_start = ea->edges[gi].start;             /* point */
            gi_end = ea->edges[gi_next].start;          /* point */
            gi_third = ea->edges[gi_prev].start;        /* point */

            ASSERT( validate_edge( ea, gate, ltable ) );
            if( touched[gate - ea->edges ] != 0 ) {
                /* we have encountered some sort of nonmanifold that
                 * was not previously detected either by create_loops()
                 * or remove_nonmanifolds(). If this condition occurs
                 * after we have encountered at least one handle, we
                 * allow the calling function to try again in the hopes
                 * that it will be resolved the next time through with 
                 * the splits introduced.  */
                COMPLAIN( "unsupported form of non-nanifold" );
                if( !has_handles )
                    status = STATUS_ERROR;
                goto done;
            }
            touched[ gi ] += 1;
            touched[ gi_next ] += 1;
            touched[ gi_prev ] += 1;
            if( ea->visitations != null ) {
                /* # of visitations pushed per triangle should match increment of 
                 *    decompression's unpack_points loop.  E.g. if we push only the gate,
                 *    the receiving side would have to increment by 3. */
                ea->visitations[ ea->visitations_used++ ] = gi;
                ea->visitations[ ea->visitations_used++ ] = gi_next;
                ea->visitations[ ea->visitations_used++ ] = gi_prev;
                ASSERT( ea->visitations_used <= ea->allocated );
            }
            if( !(loops[gi_third]) ) {
                /* Next vertex is not on any boundary.  
                 * The active loop moves inward to absorb a new vertex. */
                ops[used++] = CASE_C;
                if( associations != NULL ) {
                    associations[0] = ea->edges[gi].start;
                    associations[1] = ea->edges[gi_next].start;
                    if( !EDGE_INVALID( gate->twin ) ) {
                        int gi_twin = ea->edges[gi].twin;
                        associations[2] = ea->edges[ HPREV(gi_twin) ].start;
                    }
                    else
                        associations[2] = GARBAGE_VERTEX;
                    associations += 3;
                }
                pointmap[ v++ ] = gi_third;
                loops[gi_third] = active_loop;
                h = ea->edges + gi_next;
                h2 = ea->edges + gi_prev;
                ASSERT( !EDGE_INVALID( h->twin ) );
                ASSERT( !EDGE_INVALID( h2->twin ) );
                N[h->twin] = N[gi];
                P[N[gi]] = h->twin;
                P[h2->twin] = P[gi];
                N[P[gi]] = h2->twin;
                P[h->twin] = h2->twin;
                N[h2->twin] = h->twin;
                P[gi] = N[gi] = GARBAGE_EDGE;
                gate = ea->edges + h->twin; 
            }
            else {
                if( gi_prev == P[gi] ) {
                    if( gi_next == N[gi] ) {
                        /* Next vertex is on left AND right.  
                         * We're closing off our current loop 
                         * (and the whole model if nothing's left on the stack). */
                        ops[used++] = CASE_E;
                        ASSERT( EDGE_INVALID( ea->edges[gi_next].twin ) || 
                                    touched[ ea->edges[gi_next].twin ] );
                        ASSERT( EDGE_INVALID( ea->edges[gi_prev].twin ) || 
                                    touched[ ea->edges[gi_prev].twin ] );
                        /* look for the first edge in the stack that hasn't already been processed */
                        do {
                            if( stack.used > 0 ) {
                                gi = int_stack_pop( &stack );
                            }
                            else {
                                stack.used = -1;
                                break;
                            }
                        } while( touched[ gi ] );
                        gate = ea->edges + gi;
                        if( stack.used >= 0 ) {
                            active_loop = loops[ ea->edges[HNEXT(N[gi])].start ];
                            loops[ gi_start ] = active_loop;
                            loops[ gi_end ] = active_loop;
                            /* the following shouldn't be necessary, but do it for extra safety */
                            bi = gi;
                            do {
                                loops[ ea->edges[bi].start ] = active_loop;
                                bi = N[bi];
                            } while( bi != gi );
                            ASSERT( validate_edge( ea, gate, ltable ) );

                        }
                    }
                    else {
                        /* Next vertex is on left.  The loop has a one-triangle "wart"
                         * that can be lopped off.  Loop shortened by one vertex */
                        ops[used++] = CASE_L;
                        h = ea->edges + gi_next;
                        h2 = ea->edges + gi_prev;
                        N[h->twin] = N[gi];
                        P[h->twin] = P[gi_prev];
                        N[P[gi_prev]] = h->twin;
                        P[N[gi]] = h->twin;
                        N[gi] = P[gi] = GARBAGE_EDGE;
                        gate = ea->edges + h->twin;

                    }
                }
                else {
                    if( HNEXT(gi) == N[gi] ) {
                        /* Next vertex is on right. Short circuit one link in loop. 
                         * Operations here are symmetric to CASE_L */
                        ops[used++] = CASE_R;
                        h = ea->edges + gi_next;
                        h2 = ea->edges + gi_prev;
                        N[h2->twin] = N[gi_next];
                        P[h2->twin] = P[gi];
                        N[P[gi]] = h2->twin;
                        P[N[gi_next]] = h2->twin;
                        N[gi] = P[gi] = GARBAGE_EDGE;
                        gate = ea->edges + h2->twin;
                    }
                    else if( loops[gi_third] == active_loop ) {
                        /* CASE_S */
                        ops[used] = CASE_S;
                        h = ea->edges + gi_next;
                        h2 = ea->edges + gi_prev;
                        /* find the other side of the loop going into the vertex */
                        ASSERT( !EDGE_INVALID( h->twin ) );
                        find_loop_edge( ea, h, ltable, touched, &b );
                        if( !is_on_loop( ea, gi, ltable, gi_third) ) {
                            /* we have encountered some sort of nonmanifold that
                             * was not previously detected either by create_loops()
                             * or remove_nonmanifolds(). */
                            COMPLAIN( "unsupported form of non-nanifold" );
                            status = STATUS_ERROR;
                            goto done;
                        }
                        bi = (int)(b - ea->edges);
                        bi2 = N[bi];
                        b2 = ea->edges + bi2;
                        ASSERT( P[N[bi]] == bi );
                        ASSERT( N[P[bi]] == bi);
                        ASSERT( P[N[bi2]] == bi2 );
                        ASSERT( N[P[bi2]] == bi2);
                        ASSERT( P[N[gi]] == gi );
                        ASSERT( N[P[gi]] == gi);
                        P[bi2] = h2->twin;
                        N[h2->twin] = (int)(b2 - ea->edges);
                        P[h->twin] = (int)(b - ea->edges);
                        N[bi] = h->twin;
                        N[h->twin] = N[gi];
                        P[h2->twin] = P[gi];
                        P[N[gi]] = h->twin;
                        N[P[gi]] = h2->twin;
                        N[gi] = P[gi] = GARBAGE_EDGE;
                        gi = h->twin;
                        gate = ea->edges + gi;
                        ASSERT( P[N[bi]] == bi );
                        ASSERT( N[P[bi]] == bi );
                        ASSERT( P[N[bi2]] == bi2 );
                        ASSERT( N[P[bi2]] == bi2 );
                        ASSERT( P[N[gi]] == gi );
                        ASSERT( N[P[gi]] == gi );
                        ASSERT( validate_edge( ea, ea->edges + h2->twin, ltable ) );
                        int_stack_push( &stack, h2->twin );
                        if( 1 /* !(g_hints & HINT_NO_HANDLES) */ ) {
                            /* if case the surface has "handles", it is possible that we might 
                             * absorb the loop of the gate we just pushed in an unexpected way.  
                             * We thus give the loop a new identifier to distinguish it from 
                             * the currently active loop. When it comes time to pop the gate 
                             * back on the stack, loops[h2->twin->start] will be 0 if and only 
                             * if it has been absorbed. loops[h2->twin->end] will be 0 regardless,
                             * since it is shared between the loop that is pushed (left) and the 
                             * loop that is continued (right), and will be cleared when it is 
                             * removed from the continued loop  */
                            sloop--;
                            bi = h2->twin; 
                            ASSERT( P[N[bi]] == bi );
                            loops[ b->start ] = sloop;
                            do {
                                ASSERT( P[N[bi]] == bi );
                                bi = N[bi];
                                loops[ ea->edges[bi].start ] = sloop;
                            } while( bi != h2->twin );
                        }
                        loops[ gi_start ] = active_loop;
                        loops[ gi_end ] = active_loop;
                        /* the following shouldn't be necessary, but do it for extra safety */
                        bi = gi;
                        do {
                            loops[ ea->edges[bi].start ] = active_loop;
                            bi = N[bi];
                        } while( bi != gi );
                        ASSERT( validate_edge( ea, gate, ltable ) );
                        used++; 
                    }
                    else if( loops[gi_third] > 0 ) {
                        /* CASE_M 
                         *   Next vertex is on a loop other than the active loop (an interior loop). 
                         *   We absorb it into the current loop, and record how many vertices were added */

                        COMPLAIN( "internal error: unexpected case, CASE_M\n" );
                        status = STATUS_ERROR;
                        goto done;

                    }               
                    else {
                        /* CASE_M2
                         *   Next vertex is on a loop other than the active loop (an interior loop). 
                         *   The loop we have encountered is the left branch of a previous CASE_S.
                         *   Special handstanding is required
                         * If we have no handles, we should never get a case M2.
                         * This should trigger a STATUS_TRY_AGAIN, so the final output won't have
                         *   any case M2's */
                        ASSERT( loops[gi_third] != active_loop ); /* not an S */
                        ASSERT( loops[gi_third] < 0 ); /* not an M */
                        ops[used] = CASE_M2;
                        if((status = tear( gi, ea, pcount, 
                                &newpcount, pcount_max, mtable, ltable, remap )) <= 0 ) {
                            goto done;
                        }
                        ASSERT( gate == ea->edges + gi );

                        has_handles = 1;
                        status = STATUS_TRY_AGAIN;
                        /* the safest thing to do would be to just start over for every
                         * handle.  That costs too much performance, though.  If there are
                         * problems, re-enable the following line */
                        #if 0
                        goto done;
                        #endif

                        /* search for the S operation that created the left branch */
                        s_ops = -1;
                        for( j = 0 ; j < stack.used ; j++ ) {
                            bi2 = stack.data[ stack.used - j - 1 ];
                            if( loops[ ea->edges[ P[bi2] ].start ] == loops[ gi_third ] ) {
                                s_ops = j;
                                break;
                            }
                        }
                        if( s_ops < 0 ) {
                            /* fatal error: couldn't find the matching S operation */
                            status = STATUS_ERROR;
                            goto done;
                        }
                        status = int_stack_pop_internal( &stack, s_ops, &bi );
                        ASSERT( status == STATUS_NORMAL );
                        j = 0;  
                        /* loop overcounts by 1. decrement afterwards to compensate
                         * "j" is the number of links from the gate to the contact vertex */
                        while( ea->edges[bi].start != gi_third ){
                            bi = N[bi]; 
                            j++;
                        }
                        j--;
                        h = ea->edges + gi_next;
                        h2 = ea->edges + gi_prev;
                        /* find an edge from the other loop going into the vertex */
                        find_loop_edge( ea, h, ltable, touched, &b );
                        bi2 = bi = (int)(b - ea->edges);
                        j = 0;  
                        do {
                            /* Walk around the interior loop that we've found.  Count the vertices. */
                            ASSERT( P[N[bi]] == bi );
                            bi = N[bi];
                            j++;
                        } while( bi != bi2 );
                        bi2 = N[bi];
                        ASSERT( P[N[bi]] == bi );
                        ASSERT( N[P[bi]] == bi );
                        ASSERT( P[N[bi2]] == bi2 );
                        ASSERT( N[P[bi2]] == bi2 );
                        ASSERT( P[N[gi]] == gi );
                        ASSERT( N[P[gi]] == gi );
                        P[bi2] = h2->twin;
                        N[h2->twin] = bi2;
                        P[h->twin] = bi;
                        N[bi] = h->twin;
                        N[h->twin] = N[gi];
                        P[h2->twin] = P[gi];
                        P[N[gi]] = h->twin;
                        N[P[gi]] = h2->twin;
                        N[gi] = P[gi] = GARBAGE_EDGE;
                        gate = ea->edges + h->twin;
                        gi = (int) (gate - ea->edges);
                        ASSERT( P[N[bi]] == bi );
                        ASSERT( N[P[bi]] == bi );
                        ASSERT( P[N[bi2]] == bi2 );
                        ASSERT( N[P[bi2]] == bi2 );
                        ASSERT( P[N[gi]] == gi );
                        ASSERT( N[P[gi]] == gi );
                        used++; 
                        bi = gi;
                        do {
                            loops[ ea->edges[bi].start ] = active_loop;
                            bi = N[bi];
                        } while( bi != gi );
                        ASSERT( validate_edge( ea, ea->edges + h2->twin, ltable ) );

                    }
                }
            }
        }    
        int_stack_free( &stack );
        if (hints & HINT_ONE_PIECE )
            break;
    }

    done:
    /* in case it wasn't already done (otherwise, safe to do twice) */
    int_stack_free( &stack );
    if( touched != NULL )
        free( touched );
        
    /* there can be unreferenced vertices, but no doubly referenced vertices */
    ASSERT( v <= newpcount ); 
    if( status == STATUS_ERROR ) {
        return status;
    }
    else if( has_handles ) {
        status = STATUS_TRY_AGAIN;
    }
    else {
        status = STATUS_NORMAL;
    }
    if( opslen != NULL )
        *opslen = used;
    if( newpcount_in_out != NULL )
        *newpcount_in_out = newpcount;
    if( referenced_pcount_out != NULL )
        *referenced_pcount_out = v;
    return status;

} /* end function compute_opcodes */



/* the following functions sort an array of integers */
#define MEDIANOF3INDEX(a,b,c) (((a)>(b))?(((b)>(c))?(1):(((a)>(c))?(2):(0))):(((a)>(c))?(0):((b)>(c))?(2):(1)))
static void swap( int *a, int *b )
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
static int sort (
    int     *ileft,
    int     *iright) 
{
    int status = STATUS_NORMAL;
    if( iright - ileft == 1 )
    {
        if( *ileft > *iright )
            swap( ileft, iright );
    }
    else if( ileft < iright) {
        int             *left, *right;
        int             *candidates[3];
        int             pivot;
        int             m3i;

        candidates[0] = left = ileft;                      /* left */
        candidates[1] = ileft + ( (iright - ileft) / 2 );  /* middle */
        candidates[2] = right = iright;                    /* right */

        /* find the best pivot and move it to the far right */
        m3i = MEDIANOF3INDEX(
            *candidates[0], 
            *candidates[1],
            *candidates[2] 
        );
        pivot = *candidates[m3i];
        swap( candidates[m3i], right );

        /* should be one higher and one lower */
        ASSERT( ( *candidates[0] >= pivot ) || (*candidates[1] >= pivot ) );
        ASSERT( ( *candidates[0] <= pivot ) || (*candidates[1] <= pivot ) );

        for (;;) {
            left--;
            while (*(++left) <= pivot) 
                if( left >= right ) 
                   goto partition_done;
            swap( left, right );
            ASSERT( left < right );

            right++;
            while (*(--right) >= pivot)
                if( left >= right ) 
                   goto partition_done;
            swap( left, right );
            ASSERT( left < right );
        }
        partition_done:

        sort (ileft, left - 1 );
        sort (left + 1,  iright);
    }
    LABEL(done:);
    return status;

} /* end function sort */


static int triangles_only_len( int flen, int const *fdata, int *len_out )
{
    int const *ptr, *ptrend;
    int tcount = 0;

    ptr = fdata; 
    ptrend = fdata + flen;  
    while( ptr < ptrend ) {
        if( *ptr < 0 )
            return STATUS_ERROR; /* no support for holes in faces */
        tcount += *ptr - 2;
        ptr += *ptr + 1;
    }
    *len_out = tcount * 4;
    return STATUS_NORMAL;

} /* end function triangles_only_len */


static int triangles_only_convert( int flen_in, int const *flist_in, 
        int alter *flen_out, int alter *flist_out, 
        eb_compress_configs *configs )
{
    int status = STATUS_NORMAL;
    int const *ptr, *ptrend;
    int alter *ptrout;
    int flen = flen_in;
    int tcount = 0;
    int i;

	UNREFERENCED (configs);
    ASSERT( !(configs->hints & HINT_INPUT_BY_TRISTRIPS) );
    ptr = flist_in;
    ptrend = flist_in + flen;
    ptrout = flist_out;
    while( ptr < ptrend ) {
        tcount += *ptr - 2;
        /* create a triangle fan out of the polygon */
        for( i = 3 ; i < ptr[0] + 1 ; i++ ) {
            ptrout[0] = 3;
            ptrout[1] = ptr[1];
            ptrout[2] = ptr[i-1];
            ptrout[3] = ptr[i];
            ptrout += 4;
        }
        ptr += *ptr + 1;
    }
    *flen_out = tcount * 4;
    LABEL(done:);
    return status;

} /* end function triangles_only_convert */


/* a small utility function to zero out a small number of unused bytes */
static void clearptr( void alter *start, void alter *end )
{
    char *ptr = (char *)start;
    while( ptr < end )
        *ptr++ = 0;
}


/* Fill in defaults for configs */
static void configs_init( eb_compress_configs alter *configs )
{
    configs->bounding = NULL;
    configs->point_factor = DEFAULT_POINT_FACTOR;
    configs->x_quantization = DEFAULT_QUANTIZATION;
    configs->y_quantization = DEFAULT_QUANTIZATION;
    configs->z_quantization = DEFAULT_QUANTIZATION;
    configs->x_quantization_normals = DEFAULT_QUANTIZATION;
    configs->y_quantization_normals = DEFAULT_QUANTIZATION;
    configs->z_quantization_normals = DEFAULT_QUANTIZATION;
    configs->target_version = 100000; 
    configs->hints = DEFAULT_HINTS;
}


/* process_configs
 * Fill in whatever default values are not specified.
 * ci may be NULL, but co must not be */
static int process_configs( 
            eb_compress_configs const *ci,  
            eb_compress_configs alter *co  )
{
    int status = STATUS_NORMAL;
	int limit;

    configs_init( co );

    if( ci != NULL ) {
        co->bounding = ci->bounding;
        if( ci->point_factor != EB_DEFAULT )
            co->point_factor = ci->point_factor;
        if( ci->x_quantization != EB_DEFAULT )
            co->x_quantization = ci->x_quantization;
        if( ci->y_quantization != EB_DEFAULT )
            co->y_quantization = ci->y_quantization;
        if( ci->z_quantization != EB_DEFAULT )
            co->z_quantization = ci->z_quantization;
		if( ci->target_version >= 1000 ) 
			limit = 32;
		else
			limit = 16;
        if( co->x_quantization > limit ||
            co->y_quantization > limit ||
            co->z_quantization > limit ) {
            COMPLAIN( "specified number of bits of precision for vertices is out of range" );
            status = STATUS_ERROR;
            goto done;
        }
        /* early versions of edgebreaker didn't support normals */
        if( ci->target_version >= 651 ) {
            if( ci->x_quantization_normals != EB_DEFAULT )
                co->x_quantization_normals = ci->x_quantization_normals;
            if( ci->y_quantization_normals != EB_DEFAULT )
                co->y_quantization_normals = ci->y_quantization_normals;
            if( ci->z_quantization_normals != EB_DEFAULT )
                co->z_quantization_normals = ci->z_quantization_normals;
			if( ci->target_version >= 1000 ) 
				limit = 32;
			else
				limit = 16;
			if( co->x_quantization_normals > limit ||
				co->y_quantization_normals > limit ||
				co->z_quantization_normals > limit ) {
				COMPLAIN( "specified number of bits of precision for normals is out of range" );
				status = STATUS_ERROR;
				goto done;
			}
        }
        if( ci->hints != EB_DEFAULT ) 
            co->hints = ci->hints;
        if( ci->target_version != EB_DEFAULT )
            co->target_version = ci->target_version;
    }
  done:
    return status;

} /* end function process_configs */


/* If the bounding volume wasn't specified, we need to iterate through the points to
 * compute one. */
static int compute_bounding( 
        float const *points, int const *pointmap, 
        int pointmaplen, mtable_info alter *mtable )
{
    int status = STATUS_NORMAL;
    float x1, y1, z1; /* minimum values */
    float x2, y2, z2; /* maximum values */
    float x, y, z; /* values to compare against min and max */
    int i;

    x1 = y1 = z1 = BIG_FLOAT;
    x2 = y2 = z2 = -BIG_FLOAT;
    for( i = 0 ; i < pointmaplen ; i++ ) {
        x = points[ pointmap[i]*3 + 0 ];
        y = points[ pointmap[i]*3 + 1 ];
        z = points[ pointmap[i]*3 + 2 ];
        if( x < x1 ) x1 = x;
        if( y < y1 ) y1 = y;
        if( z < z1 ) z1 = z;
        if( x > x2 ) x2 = x;
        if( y > y2 ) y2 = y;
        if( z > z2 ) z2 = z;
    }
    mtable->flags |= MTABLE_HAS_BOUNDING;
    mtable->bounding = (ET_Bounding *) malloc ( sizeof( ET_Bounding ) );
    if( mtable->bounding == NULL ) {
        COMPLAIN( "bounding allocation failed in compute_bounding" );
        ASSERT( mtable->bounding != NULL );
        status = STATUS_ERROR;
        goto done;
    }
    mtable->bounding->x1 = x1;
    mtable->bounding->y1 = y1;
    mtable->bounding->z1 = z1;
    mtable->bounding->x2 = x2;
    mtable->bounding->y2 = y2;
    mtable->bounding->z2 = z2;
    done:
    return status;

} /* end function compute_bounding */




/* show_compress_size
 * compute a very loose upper bound on the amount of space that is going to be needed
 * after compression.  The number returned by this function should be used for allocation.
 * The function, edgebreaker compress, will then return the actual amount used (and the
 * amount that needs to be transferred) */
int show_edgebreaker_compress_size( int pcount, int flen, int const *face_data, 
        int alter *stream_len_out, int alter *pointmap_count_out, eb_compress_configs const *configs )
{
    int status = STATUS_NORMAL;
    float pfactor;
    int trilen;

    /* internal meshes have more faces (and longer longer face length) per vertex than surfaces,
     * and do not perform well with edgebreaker.  Return STATUS_ERROR so that the caller knows not
     * to use edgebreaker */
    if( pcount != 0 &&
        flen/pcount > 8 )
        return STATUS_ERROR;

    if( (status = triangles_only_len( flen, face_data, &trilen )) != STATUS_NORMAL )
        return status;

    if( configs == NULL ||
        configs->point_factor == EB_DEFAULT )
        pfactor = DEFAULT_POINT_FACTOR;
    else {
        ASSERT( configs->point_factor >= 1 );
        pfactor = configs->point_factor;
    }

    if( stream_len_out != NULL )
        *stream_len_out = (int) (
            50 +                                    /* for safety */ 
            sizeof( edgebreaker_header ) +          /* header (near-exact upper bound)*/
            2 * (trilen / 4) * sizeof(char) +       /* ops (loose upper bound)*/
            (trilen) * sizeof(int) +                /* mtable (loose upper bound)*/
            2 * (int)(pfactor * pcount * POINTSIZE) + /* normals and points (loose upper bound)*/
            8 );                                      /* a little bit of extra safety buffer */
    if( pointmap_count_out != NULL )
        *pointmap_count_out = pcount;
    LABEL(done:);
    return status;
} /* end function show_edgebreaker_compress_size */


/* the following function is unused for the moment, but left in because it helps to illustrate
 * how the remap array works. */
#if 0
static int compute_proxy_hash( 
        half_edge_array alter *ea, 
        int const *remap,
        int pcount, 
        int newpcount, 
        vhash_t *proxy_hash ) 
{
    int status = STATUS_NORMAL;
    int i, bi, proxy, new_id;

    for( i = 0 ; i < ea->used ; i++ ) {
        if( ea->edges[i].start >= pcount ) {
            new_id = ea->edges[i].start | 0x80000000;
            proxy = remap[ea->edges[i].start - pcount];
            while( proxy >= pcount )
                proxy = remap[proxy - pcount];
            if( proxy == GARBAGE_VERTEX )
                /* a dummy */
                vhash_insert_item( proxy_hash, I2V(new_id), I2V(DUMMY_VERTEX) );
            else
                /* an alias */
                vhash_insert_item( proxy_hash, I2V(new_id), I2V(proxy) );
            bi = i;
            ea->edges[i].start = new_id;
            /* clockwise */
            while( (ea->edges[bi].twin != GARBAGE_EDGE) && (bi != i) ) {
                ASSERT( !EDGE_INVALID( ea->edges[bi].twin ) );
                ea->edges[bi].start = new_id;
                bi = ea->edges[bi].twin;
                bi = HNEXT(bi);
            }
            if( bi != i ) {
                bi = HPREV(i);
                /* counter clockwise */
                while( ea->edges[bi].twin != GARBAGE_EDGE ) {
                    ASSERT( !EDGE_INVALID( ea->edges[bi].twin ) );
                    ea->edges[ea->edges[bi].twin].start = new_id;
                    bi = ea->edges[bi].twin;
                    bi = HPREV(bi);
                }
            }
        }
    }
  LABEL(done:)
    return status;
}
#endif


/* renumber each start vertex with id>pcount back to the proxy vertex with which they 
 * share their location */ 
static int map_to_proxies( 
        half_edge_array alter *ea, 
        int const *remap,
        int pcount, 
        vhash_t *proxy_hash ) 
{
    int status = STATUS_NORMAL;
    int i, proxy;

    UNREFERENCED(proxy_hash);

    for( i = 0 ; i < ea->used ; i++ ) {
        if( ea->edges[i].start >= pcount ) {
            proxy = remap[ea->edges[i].start - pcount];
            while( proxy >= pcount )
                proxy = remap[proxy - pcount];
            if( proxy == GARBAGE_VERTEX )
                proxy = DUMMY_VERTEX;
            ea->edges[i].start = proxy;
            //xxx this assert will go away once we start having multiple normals per vertex
            ASSERT( proxy >= 0 || proxy == DUMMY_VERTEX );
        }
    }
  LABEL(done:)
    return status;
}


/* edgebreaker_compress
 * Very little work is done here.  The intent of this function is simply to allocate
 * any temporary data structures and make the calls to the sub-pieces so we can present
 * a clean external interface */
int edgebreaker_compress( int pcount, float const *points, float const *normals, 
                int flen_in, int const *flist_in,
                int alter *stream_len_in_out, void alter *stream_out,
                int alter *pointmap_len_in_out, int alter *pointmap_out, 
                eb_compress_configs const *configs_in )
{
    int i, j, pcount_max, newpcount, opcodes_pcount = 0, opslen = 0, mtablelen, status, offset = 0, shift;
    int flen, flen_required, available;
    int *flist = NULL, *pointmap = NULL, *inverse_pointmap = NULL;
    int *remap = NULL, *associations = NULL;
    /* opcodes are character data, so no need to align them */
    char *opcodes = NULL;
    half_edge_array ea;
    edgebreaker_header *hptr = NULL;
    mtable_info mtable;
    loop_table ltable = { NULL, NULL, 0, 0 };
    char alter *dummies = NULL;
    eb_compress_configs configs;
    float pfactor;
    int *quantized_points = NULL;
    int *quantized_normals = NULL;
    vhash_t *proxy_hash = NULL;  //mapping from alias vertices to the original with which it shares a location
    vhash_t *tristrip_hash = NULL; //mapping from id's of edges that start tristrips to the place in flist where the tristrip starts 
    bool by_tristrips;
    ET_Bounding normal_bbox = { -1,-1,-1, 1,1,1 };

    /* fill in whatever default values are missing */
    if((status = process_configs( configs_in, &configs )) <= 0 )
        /* whereas from most places we would jump to "done", we haven't yet allocated,
         * so there's nothing to clean up */
        return status;  
    pfactor = configs.point_factor;
    mtable_info_init( &mtable );

    flen = flen_in;
    hptr = (edgebreaker_header *) stream_out;
    memset( hptr, 0, sizeof( edgebreaker_header ) );
    /* Most surfaces have tri=2*points.  half edges are 3*tri. 
     * The half edge array can afford to have a slightly lesser buffer, 
     * though because it is designed to grow (thus pcount, not pcount_max) */
    if(( status = half_edge_array_init( &ea, pcount * 8 ) ) <= 0 ) {
        if(( status = half_edge_array_init( &ea, pcount * 6 ) ) <= 0 ) {
            goto done;
        }
    }
    pcount_max = (int)(pfactor * pcount);
    pointmap = (int *) malloc ( pcount_max * sizeof(int) );
    memset( pointmap, 0, pcount_max * sizeof(int) );
    remap = (int *) malloc ( (2 + pcount_max - pcount) * sizeof(int) );
    memset( remap, 0x80, (pcount_max - pcount) * sizeof(int) );
    if( pointmap == NULL || remap == NULL ) {
        COMPLAIN( "pointmap or mtable allocation failed in function edgebreaker_compress\n" );
        status = STATUS_ERROR;
        goto done;
    }

    by_tristrips = (configs.hints & HINT_INPUT_BY_TRISTRIPS) != 0;
    triangles_only_len( flen_in, flist_in, &flen_required );
    if( (flen_required != flen) &&
        !by_tristrips ) {
        flist = (int *) malloc ( flen_required * sizeof( int ) );
        if( flist == NULL ) {
            COMPLAIN( "flist array allocation failed" );
            status = STATUS_ERROR;
            goto done;
        }
        if((status = triangles_only_convert( flen_in, flist_in, &flen, flist, &configs )) <= 0 )
            goto done;
    }
    else { 
        /* we cheat here, and typecast to "alter" so we can put it in the same place as
         * the above constructed array, but we won't change it -- we promise */
        flist = (int alter *) flist_in;
    }

    if((status = half_edge_array_convert( pcount, pcount_max, flen, flist, by_tristrips,
            &ea, &mtable, configs.hints, &newpcount, &ltable, remap, &tristrip_hash )) <= 0 )
        goto done;

    if(configs.target_version >= 906 )
        hptr->scheme = 2;
    else if(configs.target_version >= 651)
        hptr->scheme = 1;
    else
        hptr->scheme = 0;
    switch( hptr->scheme ) {
        case 0:
            offset = (int)sizeof(edgebreaker_header0);
        break;
        case 1:
        case 2:
            offset = (int)sizeof(edgebreaker_header1);
        break;
        default:
            COMPLAIN( "internal error: unrecognized edgebreaker data format\n" );
    }
    opcodes = (char *) stream_out + offset;  /* assumes sizeof header is 4-byte aligned */

    if( hptr->scheme >= 2 ) { 
        ea.visitations = (int *) malloc ( ea.allocated * sizeof( int ) );
    }
    else {
        associations = (int *) malloc ( 3 * pcount_max * sizeof( int ) );
        if( associations == NULL ) {
            COMPLAIN( "associations array allocation failed in function edgebreaker_compress\n" );
            status = STATUS_ERROR;
            goto done;
        }
    }

    j = 0;
    /* allow compute_opcodes just a few tries to get it right 
     * (then abort if it doesn't) */
    while( j < 3 ) {
        status = compute_opcodes( 
            &ea, configs.hints, pcount, pcount_max,		/* input */
            &newpcount,                                 /* input and output */
            &opslen, opcodes, &ltable, pointmap, remap, /* output */
            &mtable, associations, &opcodes_pcount);    /* output */
        if( status == STATUS_NORMAL ) {
            break;
        }
        else if( status <= 0 ) {
            goto done;
        }
        else if( status == STATUS_TRY_AGAIN ) {
            by_tristrips = false;
            mtable.mlengths_used = 0;
            mtable.m2stackoffsets_used = 0;
            mtable.m2gateoffsets_used = 0;
            for( i = 0 ; i < newpcount ; i++ ) {
                ltable.loops[i] = 0;
            }
            if((status = create_loops( 
                    NULL, &ea, pcount, pcount_max, 
                    &newpcount, &ltable, remap    
                )) <= 0 )
                goto done;
            if((status = plug_all_holes( 
                    &ea, NULL, pcount, pcount_max,
                    &newpcount, &mtable, &ltable, remap
                )) <= 0 )
                goto done;
        }
        j++;
    }

    dummies = (char *) malloc ( newpcount * sizeof( char ) );
    if( dummies == NULL ) {
        COMPLAIN( "dummies array allocation failed in function edgebreaker_compress" );
        status = STATUS_ERROR;
        goto done;
    }
    memset( dummies, 0, newpcount * sizeof( char ) );

    /* Any value in pointmap that is at or above the original point count is either
     * a copy of some other vertex (i.e. alias) or a dummy.  Use a while loop instead of an 
     * if statement because it could be a copy of a copy (of a copy of a copy ad nauseum) */
    for( i = 0 ; i < newpcount; i++ ) {
        if( pointmap[i] >= pcount )  {
            while( pointmap[i] >= pcount )  {
                pointmap[i] = remap[ pointmap[i] - pcount ];
                if( pointmap[i] == DUMMY_VERTEX || pointmap[i] == GARBAGE_VERTEX ) {
                    /* a dummy or an alias of a dummy */
                    if((status = mtable_info_append_dummy( &mtable, i )) <= 0)
                        goto done;
                    dummies[i] = 1;
                }
            }
        }
    }

    /* Sort the dummies now that we have the remapped values */
    if( mtable.dummies_used > 1 ) {
        sort( mtable.dummies,  mtable.dummies + mtable.dummies_used - 1 );
    }
    /* for each original vertex, inverse_pointmap tracks which new vertex is the first to reference it.
     * allows us to avoid multiple references */
    inverse_pointmap = (int *) malloc ( pcount * sizeof( int ) );
    if( inverse_pointmap == NULL ) {
        COMPLAIN( "inverse_pointmap allocation failed in function edgebreaker_compress" );
        status = STATUS_ERROR;
        goto done;
    }
    /* initialize to garbage so we can recognize unreferenced vertices */
    memset( inverse_pointmap, 0x80, pcount * sizeof( int ) ); 
    shift = 0;
    for( i = 0 ; i < opcodes_pcount ; i++ ) {
        ASSERT( pointmap[i] < pcount );
        if( pointmap[i] == DUMMY_VERTEX || pointmap[i] == GARBAGE_VERTEX ) {
            /* a dummy */
            shift++;
            continue;
        }
        ASSERT( !VERTEX_SPECIAL( pointmap[i] ) );
        if( inverse_pointmap[ pointmap[i] ] != GARBAGE_VERTEX ) {
            /* that particular vertex was already claimed. Use the patches
             * array to create an alias for it */
            if(( status = mtable_info_append_patch( &mtable, i )) <= 0 )
                goto done;
            if(( status = mtable_info_append_patch( &mtable, inverse_pointmap[ pointmap[i] ] )) <= 0 )
                goto done;
            shift++;
        }
        else {
            /* we're the first to use this particular vertex.  Claim it by
             * storing the information needed to create an alias.  Aliases
             * will not appear in the final pointmap, so we need to shift
             * to the left by the number of aliases that we have encountered
             * so far. */
            pointmap[ i - shift ] = pointmap[i];
            inverse_pointmap[ pointmap[i] ] = i - shift;
        }
    }    
    /* this shouldn't be necessary, but make sure we don't leave anything to chance */
    memset( pointmap + newpcount - shift, 0x80, shift * sizeof( int ) );

    /* Remove entries in the associations array that predict the location of dummies. */
    if( associations != NULL ) {
        shift = 0;
        for( i = 0 ; i < newpcount ; i++ ) {
            if( dummies[ i ] ) {
                shift += 3;
            }
            else {
                associations[ i*3 + 0 - shift ] = associations[ i*3 + 0 ];
                associations[ i*3 + 1 - shift ] = associations[ i*3 + 1 ];
                associations[ i*3 + 2 - shift ] = associations[ i*3 + 2 ];
            }
        }
    }
    /* now adjust the point count downwards to account for unreferenced vertices */
    shift = 0;
    for( i = 0 ; i < pcount ; i++ ) {
        if( inverse_pointmap[i] == GARBAGE_VERTEX )
            shift++;
    }

    hptr->opslen = opslen;
    hptr->mtablelen = -1; /*  value not known until later on. */
    hptr->pointslen = -1; /*  value not known until later on. */
    hptr->pcount = pcount - shift; /* input point count minus the number of unreferenced vertices */

    /* mtable */
    if( configs_in == NULL ||
        configs_in->bounding == NULL ) {
        /* if we weren't given a bbox, calculate and put one in the mtable if we can */
        if( points != NULL )
            compute_bounding( points, pointmap, hptr->pcount, &mtable ); 
	else if( configs.target_version <= 1024 && points == NULL && normals != NULL ) {
	    /* work around a bug that existed in readers prior to 1024 */
	    mtable.bounding = (ET_Bounding *) malloc ( sizeof( ET_Bounding ) );
	    memcpy( mtable.bounding, &normal_bbox, sizeof(ET_Bounding) );
	}
    }
    mtable.x_quantization = configs.x_quantization;
    mtable.y_quantization = configs.y_quantization;
    mtable.z_quantization = configs.z_quantization;
    mtable.x_quantization_normals = configs.x_quantization_normals;
    mtable.y_quantization_normals = configs.y_quantization_normals;
    mtable.z_quantization_normals = configs.z_quantization_normals;

    /* mtable data */
    offset = offset + hptr->opslen;
    clearptr( (char *)stream_out + offset, (char *)stream_out + offset + TONEXT4(offset) );
    offset += TONEXT4(offset);          /* 4-byte align it */
    pack_mtable( &mtable, ((char *)stream_out + offset), &mtablelen );
    hptr->mtable_scheme = 0;
    hptr->mtablelen = mtablelen;
    offset = offset + hptr->mtablelen;
    offset += TONEXT4(offset);          /* 4-byte align it */

    /* for the purpose of parallelogram completion, associations refer to original, unremapped, vertices */
    /* remap associations back to the original points with real locations  */
    if( associations != NULL ) {
        for( i = 0 ; i < 3*(pcount - shift) ; i++ ) {
            while( associations[i] >= pcount ) {
                associations[i] = remap[ associations[i] - pcount ];
            }
        }
    }

    clearptr( (char *)stream_out + offset, (char *)stream_out + offset + TONEXT4(offset) );
    available = *stream_len_in_out - offset;
    if( hptr->scheme >= 2 ) {
        ET_Bounding *bbox = ( configs.bounding ? configs.bounding : mtable.bounding );

        ASSERT( configs.target_version >= 906 );
        if( points != NULL ) {
            hptr->points_scheme = 3;
            quantized_points = (int *)malloc( pcount * 3 * sizeof( int ) );
            if((status = quantize_points( bbox, pcount, points,                 /* input */
                        configs.x_quantization, configs.y_quantization, configs.z_quantization, /* input */
                        quantized_points                                        /* output */
                    )) <= 0 )
                goto done;
        }
        else
            hptr->points_scheme = 0;
        if( normals != NULL ) {
            hptr->normals_scheme = 3;
            quantized_normals = (int *)malloc( pcount * 3 * sizeof( int ) );
            if((status = quantize_normals( &normal_bbox, pcount, normals,       /* input */
                        configs.x_quantization_normals, configs.y_quantization_normals, configs.z_quantization_normals, /* input */
                        quantized_normals                                       /* output */
                    )) <= 0 )
                goto done;
        }
        else
            hptr->normals_scheme = 0;
        proxy_hash = new_vhash( 100, malloc, free );
        status = map_to_proxies( &ea, remap, pcount, proxy_hash );
        status = pack_points_and_normals(
                    hptr,                                                   /* input/output */
                    &ea, pcount, newpcount,                                 /* input */
                    quantized_points, quantized_normals,                    /* input (may be null) */
                    dummies, proxy_hash, by_tristrips,                      /* input */
                    tristrip_hash, available,                               /* input */
                    (char *)stream_out + offset );                          /* output */
        if( status <= 0 )
            goto done;
        offset += hptr->pointslen;
        offset += TONEXT4(offset);              /* 4-byte align it */
    }
    else {
        /* point data */
        if( points != NULL ) {
            if( configs.target_version > 600 )
                hptr->points_scheme = 1;
            else
                hptr->points_scheme = 0;
            ASSERT( associations != NULL );
            if((status = old_pack_points( 
                        &mtable, associations, 
                        hptr, pcount, pointmap, points, 
                        available, 
                        (char *)stream_out + offset,  
                        &configs )) <= 0 )
                goto done;
            offset += hptr->pointslen;
            offset += TONEXT4(offset);              /* 4-byte align it */
        }
        else {
            hptr->points_scheme = 0;
            hptr->pointslen = 0;
        }
        /* normals data */
        if((configs.target_version >= 651) &&
           (normals != NULL)) {
            ASSERT( hptr->scheme >= 1 ); /* normals should be null unless scheme < 1 */
            clearptr( (char *)stream_out + offset, (char *)stream_out + offset + TONEXT4(offset) );
            hptr->normals_scheme = 0;
            available = *stream_len_in_out - offset;
            if((status = old_pack_normals(
                        &mtable, associations, 
                        hptr, pcount, pointmap, normals, 
                        available,
                        (char *)stream_out + offset, 
                        &configs )) <= 0 )
                goto done;
            offset += hptr->normalslen;
            offset += TONEXT4(offset);              /* 4-byte align it */
        }
        else {
            hptr->normals_scheme = 0;
            if( hptr->scheme >= 1 )
                hptr->normalslen = 0;
        }
    }

    if( pointmap_len_in_out != NULL ) {
        ASSERT( *pointmap_len_in_out >= pcount );
        *pointmap_len_in_out = hptr->pcount;
        if( pointmap_out != NULL ) {
            for( i = 0 ; i < hptr->pcount ; i++ ) {
                pointmap_out[i] = pointmap[i];
            }
        }
    }
    if( stream_len_in_out != NULL )
        *stream_len_in_out = offset;

   done:
    /* clean up all of the memory we allocated as local scratch space */
    if( tristrip_hash != NULL )
	delete_vhash( tristrip_hash );
    if( proxy_hash != NULL )
        delete_vhash( proxy_hash );
    if( quantized_points != NULL )
        free( quantized_points );
    if( quantized_normals != NULL )
        free( quantized_normals );
    if( dummies != NULL )
        free( dummies );
    if( inverse_pointmap != NULL )
        free( inverse_pointmap );

    if( associations != NULL )
        free( associations );
    if( pointmap != NULL )
        free( pointmap );
    if( remap != NULL )
        free( remap );
    loop_table_free( &ltable );
    mtable_info_free( &mtable );
    if( flist != flist_in && flist != NULL )
        free( flist );
    half_edge_array_free( &ea );

    /* adjust for big endian (that is, if STREAM_BIGENDIAN is defined) */

    hptr->opslen = swap32( hptr->opslen );
    hptr->mtablelen = swap32( hptr->mtablelen );
    hptr->pointslen = swap32( hptr->pointslen );
    hptr->pcount = swap32( hptr->pcount );

    return status;
} /* end function edgebreaker_compress */

#endif //BSTREAM_DISABLE_EDGEBREAKER
#endif //BSTREAM_READONLY

