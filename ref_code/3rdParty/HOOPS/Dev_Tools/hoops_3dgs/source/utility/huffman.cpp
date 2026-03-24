/*
* Copyright (c) 1998 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.  Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: huffman.cpp,v 1.30 2010-12-07 01:12:32 jason Exp $
*/



#ifdef HOOPS_DEFINED
#define VList HVList
#define VHash HVHash
#define HUFFMAN_BIGENDIAN HOOPS_BIGENDIAN
#else 
#include "vlist.cpp"
#include "vhash.cpp"

#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW new
#endif

#ifndef INLINE
#		define	INLINE		inline
#endif

#ifndef UNREFERENCED
#define UNREFERENCED(param) ((void)(param))
#endif

typedef VHash<unsigned short, int> VHashDictionary;


struct huffman_encode_table_t
#ifdef HOOPS_DEFINED
	: public CMO
#endif
{
	unsigned short value;
	unsigned short count;
};

typedef VHash<unsigned short, huffman_encode_table_t*> EncodeTable;

struct huffman_decode_table_8_t{
	unsigned char value;
	unsigned char count;
};

struct huffman_decode_table_16_t{
	unsigned short value;
	unsigned char count;
};

struct huffman_tree_node_t 
#ifdef HOOPS_DEFINED
	: public CMO
#endif
{
	int weight;
	unsigned short value;
	struct huffman_tree_node_t *left;
	struct huffman_tree_node_t *right;
};

typedef VList<huffman_tree_node_t*> VListHuffTree;


struct huffman_encoder_8_t{
	VHashDictionary *histogram;

	huffman_decode_table_8_t *decode_table;
	EncodeTable *encode_table;
					
	int decode_table_size;
	int decode_bits;
 
};

struct huffman_encoder_16_t{
	VHashDictionary *histogram;
	huffman_decode_table_16_t *decode_table;

	EncodeTable *encode_table;
				
	int decode_table_size;
	int decode_bits;
 
};

INLINE short fixup_short (short s) {
#if HUFFMAN_BIGENDIAN
	unsigned char c1, c2;

	c1 = s & 255;
	c2 = (s >> 8) & 255;

	return (c1 << 8) + c2;
#else
	return s;
#endif
}

INLINE int fixup_int (int i) {
#if HUFFMAN_BIGENDIAN
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
#else
	return i;
#endif
}

static int sort_hufftree_by_weight(huffman_tree_node_t *a, huffman_tree_node_t *b, void const * const data)
{
	UNREFERENCED(data);

	if (a->weight == b->weight)
		return 0;
	else if (a->weight > b->weight)
		return 1;
	else
		return -1;
}

huffman_encoder_8_t * new_huffman_encoder_8() 
{
#ifdef HOOPS_DEFINED
	huffman_encoder_8_t *he;
	ALLOC(he, huffman_encoder_8_t);
	he->histogram = POOL_NEW(HOOPS_WORLD->memory_pool, VHashDictionary)(HOOPS_WORLD->memory_pool);
	he->encode_table = POOL_NEW(HOOPS_WORLD->memory_pool, EncodeTable)(HOOPS_WORLD->memory_pool);
#else
	huffman_encoder_8_t *he = (huffman_encoder_8_t *)malloc(sizeof(huffman_encoder_8_t));
	he->histogram = NEW(VHashDictionary)();
	he->encode_table = NEW(EncodeTable)();
#endif
	he->decode_table = 0;
	return he;
}

huffman_encoder_16_t * new_huffman_encoder_16() 
{
#ifdef HOOPS_DEFINED
	huffman_encoder_16_t *he;
	ALLOC(he, huffman_encoder_16_t);
	he->histogram = POOL_NEW(HOOPS_WORLD->memory_pool, VHashDictionary)(HOOPS_WORLD->memory_pool);
	he->encode_table = POOL_NEW(HOOPS_WORLD->memory_pool, EncodeTable)(HOOPS_WORLD->memory_pool);
#else
	huffman_encoder_16_t *he = (huffman_encoder_16_t *)malloc(sizeof(huffman_encoder_16_t));
	he->histogram = NEW(VHashDictionary)();
	he->encode_table = NEW(EncodeTable)();
#endif
	he->decode_table = 0;
	return he;
}


void delete_huffman_encoder_8(huffman_encoder_8_t *he) 
{
	delete he->histogram;
	he->encode_table->DeleteItems();
	delete he->encode_table;
#ifdef HOOPS_DEFINED
	if (he->decode_table)
		FREE_ARRAY(he->decode_table, he->decode_table_size, huffman_decode_table_8_t);
	FREE(he, huffman_encoder_8_t);
#else
	delete [] he->decode_table;
	free(he);
#endif

}

void delete_huffman_encoder_16(huffman_encoder_16_t *he) 
{
	delete he->histogram;
	he->encode_table->DeleteItems();
	delete he->encode_table;
#ifdef HOOPS_DEFINED
	if (he->decode_table)
		FREE_ARRAY(he->decode_table, he->decode_table_size, huffman_decode_table_16_t);
	FREE(he, huffman_encoder_16_t);
#else
	delete [] he->decode_table;
	free(he);
#endif
}

void huffman_add_data_8(huffman_encoder_8_t *he, int in_n, const char *in_data)
{
	while(in_n--) {
		unsigned short temp = (unsigned short)*in_data;
		int count = he->histogram->Lookup(temp);
		if (count == 0)
			he->histogram->InsertItem(temp, 1);
		else
			he->histogram->ReplaceItem(temp,++count);
		in_data++;
	}
}

void huffman_add_data_16(huffman_encoder_16_t *he, int in_n, const unsigned short *in_data)
{
	while(in_n--) {
		unsigned short temp = *in_data;
		int count = he->histogram->Lookup(temp);
		if (count == 0)
			he->histogram->InsertItem(temp, 1);
		else
			he->histogram->ReplaceItem(temp,++count);
		in_data++;
	}
}

static void chop_hufftree(huffman_tree_node_t *root) {
	if (root->left)
		chop_hufftree(root->left);
	if (root->right)
		chop_hufftree(root->right);
	delete root;
}

void huffman_create_tables_8(huffman_encoder_8_t *he)

{
	he->decode_table_size=2048;
	he->decode_bits=0;

#ifdef HOOPS_DEFINED
	VListHuffTree *hufftree = POOL_NEW(HOOPS_WORLD->memory_pool, VListHuffTree)(HOOPS_WORLD->memory_pool);
#else
	VListHuffTree *hufftree = NEW(VListHuffTree)();
#endif

	VHashDictionary::Pair *item;
	VHashDictionary::PairList *dictionary = he->histogram->GetPairList();
	dictionary->ResetCursor();
	int dictionary_length = dictionary->Count();
	for (int i=0; i<dictionary_length; i++) {
		item = dictionary->PeekCursor();
		huffman_tree_node_t *newnode = NEW(huffman_tree_node_t);
		newnode->value = item->Key();
		newnode->weight = item->Item();
		newnode->left = newnode->right = 0;
		hufftree->AddSorted(newnode, sort_hufftree_by_weight);

		dictionary->AdvanceCursor();
	}
	delete dictionary;

	while (hufftree->Count() > 1) {
		huffman_tree_node_t *newnode = NEW(huffman_tree_node_t);
		newnode->left = hufftree->RemoveFirst();
		newnode->right = hufftree->RemoveFirst();
		newnode->weight = newnode->left->weight + newnode->right->weight;
		newnode->value = 0; //internal nodes
		hufftree->AddSorted(newnode, sort_hufftree_by_weight);
	}

	huffman_tree_node_t *root = hufftree->PeekFirst();

	for (int i=0; i<he->decode_table_size; i++) {
		/* find depth and make encode table */
		huffman_tree_node_t *walker = root;
		int this_decode_bits = 0;
		int bitblob = i;

		while (walker->left || walker->right) {
			if (bitblob & 1)
				walker = walker->right;
			else
				walker = walker->left;
			bitblob >>= 1;
			this_decode_bits++;
		}

		if (this_decode_bits > he->decode_bits)
			he->decode_bits = this_decode_bits;

		if (!he->encode_table->LookupItem(walker->value)) {
			huffman_encode_table_t *encode_table_item = NEW(huffman_encode_table_t);
			encode_table_item->value = i & ((1 << this_decode_bits)-1);
			encode_table_item->count = this_decode_bits;
			he->encode_table->InsertItem(walker->value, encode_table_item);
		}
	}

	he->decode_table_size = 1;
	he->decode_table_size <<= he->decode_bits; //must accommodate 2^(decode_bits) codes

#ifdef HOOPS_DEFINED
	ALLOC_ARRAY(he->decode_table, he->decode_table_size, huffman_decode_table_8_t);
#else
	he->decode_table = new huffman_decode_table_8_t[he->decode_table_size];
#endif

	for (int i=0; i<he->decode_table_size; i++) {
		/* now make decode table */
		huffman_tree_node_t *walker = root;
		int this_decode_bits = 0;
		int bitblob = i;

		while (walker->left || walker->right) {
			if (bitblob & 1)
				walker = walker->right;
			else
				walker = walker->left;
			bitblob >>= 1;
			this_decode_bits++;
		}

		he->decode_table[i].value = (unsigned char)walker->value;
		he->decode_table[i].count = this_decode_bits;
	}
	//clean up tree structure
	chop_hufftree(hufftree->PeekFirst());
	delete hufftree;

	delete he->histogram;
	he->histogram=0;
}

void huffman_create_tables_16(huffman_encoder_16_t *he)
{
	he->decode_table_size=65536;
	he->decode_bits=0;

#ifdef HOOPS_DEFINED
	VListHuffTree *hufftree = POOL_NEW(HOOPS_WORLD->memory_pool, VListHuffTree)(HOOPS_WORLD->memory_pool);
#else
	VListHuffTree *hufftree = NEW(VListHuffTree)();
#endif

	VHashDictionary::Pair *item;
	VHashDictionary::PairList *dictionary = he->histogram->GetPairList();
	dictionary->ResetCursor();
	int dictionary_length = dictionary->Count();
	for (int i=0; i<dictionary_length; i++) {
		item = dictionary->PeekCursor();
		huffman_tree_node_t *newnode = NEW(huffman_tree_node_t);
		newnode->value = item->Key();
		newnode->weight = item->Item();
		newnode->left = newnode->right = 0;
		hufftree->AddSorted(newnode, sort_hufftree_by_weight);

		dictionary->AdvanceCursor();
	}
	delete dictionary;

	while (hufftree->Count() > 1) {
		huffman_tree_node_t *newnode = NEW(huffman_tree_node_t);
		newnode->left = hufftree->RemoveFirst();
		newnode->right = hufftree->RemoveFirst();
		newnode->weight = newnode->left->weight + newnode->right->weight;
		newnode->value = 0; //internal nodes
		hufftree->AddSorted(newnode, sort_hufftree_by_weight);
	}

	huffman_tree_node_t *root = hufftree->PeekFirst();

	for (int i=0; i<he->decode_table_size; i++) {
		/* find depth and make encode table */
		huffman_tree_node_t *walker = root;
		int this_decode_bits = 0;
		int bitblob = i;

		while (walker->left || walker->right) {
			if (bitblob & 1)
				walker = walker->right;
			else
				walker = walker->left;
			bitblob >>= 1;
			this_decode_bits++;
		}

		if (this_decode_bits > he->decode_bits)
			he->decode_bits = this_decode_bits;

		if (!he->encode_table->LookupItem(walker->value)) {
			huffman_encode_table_t * encode_table_item = NEW(huffman_encode_table_t);
			encode_table_item->value = i & ((1 << this_decode_bits)-1);
			encode_table_item->count = this_decode_bits;
			he->encode_table->InsertItem(walker->value, encode_table_item);
		}
	}

	he->decode_table_size = 1;
	he->decode_table_size <<= he->decode_bits; //must accommodate 2^(decode_bits) codes

#ifdef HOOPS_DEFINED
	ALLOC_ARRAY(he->decode_table, he->decode_table_size, huffman_decode_table_16_t);
#else
	he->decode_table = new huffman_decode_table_16_t[he->decode_table_size];
#endif

	for (int i=0; i<he->decode_table_size; i++) {
		/* now make decode table */
		huffman_tree_node_t *walker = root;
		int this_decode_bits = 0;
		int bitblob = i;

		while (walker->left || walker->right) {
			if (bitblob & 1)
				walker = walker->right;
			else
				walker = walker->left;
			bitblob >>= 1;
			this_decode_bits++;
		}

		he->decode_table[i].value = (unsigned short)walker->value;
		he->decode_table[i].count = this_decode_bits;
	}
	//clean up tree structure
	chop_hufftree(hufftree->PeekFirst());
	delete hufftree;
	
	delete he->histogram;
	he->histogram=0;
}

bool huffman_encode_8(huffman_encoder_8_t *he,
					int in_n, const char *in_data,
					int *out_data_bits, char *out_data)
{
	if (he->decode_bits > 16)
		return false;

	*out_data_bits=0;
	memset(out_data, 0, sizeof(char) * (in_n));
	
	int i=0;
	while (1) {
		huffman_encode_table_t *code = he->encode_table->Lookup((unsigned char)in_data[i]);
		if (!code)
			return false; //code not found in dictionary; cannot encode
		unsigned int value = (unsigned int)code->value;
		int count = (int)code->count;
		int index = *out_data_bits/8;
		int offset = *out_data_bits%8;
		*out_data_bits += count;

		if ((*out_data_bits + 7) / 8 > in_n)
			return false;

		if (in_n - index > 3) {
			unsigned int shifted = fixup_int(value << offset);
			*((unsigned int *)&out_data[index]) |= shifted;
		}
		else if (in_n - index == 3) {
			unsigned int shifted = value << offset;
			out_data[index]   |= (shifted)		 & 255;
			out_data[index+1] |= (shifted >>  8) & 255;
			out_data[index+2] |= (shifted >> 16) & 255;
		}
		else if (in_n - index == 2) {
			unsigned short shifted = fixup_short(value << offset);
			*((unsigned short *)&out_data[index]) |= shifted;
		}
		else if (in_n - index == 1) {
			unsigned char * block = (unsigned char *)&out_data[index];
			*block |= value << offset;
		}

		if (++i == in_n)
			break;
	}

	return true;
}

bool huffman_encode_16(huffman_encoder_16_t *he,
					int in_n,	const unsigned short *in_data,
					int *out_data_bits, unsigned short *out_data)
{
	if (he->decode_bits > 16)
		return false;

	*out_data_bits=0;
	memset(out_data, 0, sizeof(unsigned short) * (in_n));

	int i=0;
	while (1) {
		huffman_encode_table_t *code = he->encode_table->Lookup((unsigned short)in_data[i]);
		if (!code)
			return false; //code not found in dictionary; cannot encode
		unsigned int value = (unsigned int)code->value;
		int count = (int)code->count;
		int index = *out_data_bits/16;
		int offset = *out_data_bits%16;
		*out_data_bits += count;

		if ((*out_data_bits + 15) / 16 > in_n)
			return false;

		if (in_n - index > 2) {
			unsigned int shifted = fixup_int(value << offset);
			*((unsigned int *)&out_data[index]) |= shifted;
		}
		else if (in_n - index == 1) {
			unsigned short shifted = value << offset;
			out_data[index]   |= (shifted) & 65535;
		}

		if (++i == in_n)
			break;
	}

	return true;
}

void huffman_decode_8(huffman_encoder_8_t *he, int in_data_bits, const char *in_data, int *out_n, char *out_data) 
{
	unsigned int decoder_mask = (1<<he->decode_bits)-1;
	unsigned int current = 0;
	int current_bits = 0;
	int counted_bits = 0;
	int n=0;
	int in_n = (in_data_bits + 7) / 8;

	*out_n=0;

	while (1) {

		huffman_decode_table_8_t *entry; 

		while (current_bits < he->decode_bits) {

			if (n++ >= in_n) 
				break;

			current |= (((unsigned char)*in_data++) << current_bits);
			current_bits += 8;
		}

		entry = &he->decode_table[current & decoder_mask];
		
		current >>= entry->count;
		
		current_bits -= entry->count;
		
		out_data[(*out_n)++] = entry->value;

		if ( (counted_bits += entry->count) == in_data_bits)  //have we counted all the bits?
			break;

	}
}

void huffman_decode_16(huffman_encoder_16_t *he, int in_data_bits, const unsigned short *in_data, int *out_n, unsigned short *out_data) 
{
	unsigned int decoder_mask = fixup_int((1<<he->decode_bits)-1);
	unsigned int current = 0;
	int current_bits = 0;
	int counted_bits = 0;
	int n=0;
	int in_n = (in_data_bits + 15) / 16;

	*out_n=0;

	while (1) {

		huffman_decode_table_16_t *entry; 

		while (current_bits < he->decode_bits) {

			if (n++ >= in_n) 
				break;

			current |= fixup_int(((fixup_short(*in_data++) & 65535) << current_bits));

			current_bits += 16;
		}

		entry = &he->decode_table[fixup_int(current & decoder_mask)];

		current = fixup_int(fixup_int(current) >> entry->count);

		current_bits -= entry->count;

		out_data[(*out_n)++] = entry->value;

		if ( (counted_bits += entry->count) == in_data_bits) //have we counted all the bits?
			break;
	}
}


