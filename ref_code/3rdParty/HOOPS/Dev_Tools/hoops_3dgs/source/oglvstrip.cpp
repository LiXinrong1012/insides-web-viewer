/*
 * Copyright (c) by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.35 2010-11-30 22:02:20 heppe Exp $
 *
 * This file contains the cases from draw_3d_tristrip that do not have any face
 * attributes (i.e. NFC, NFN).
 */

#if defined(GLX_DRIVER) || defined(WGL_DRIVER) || defined(AGL_DRIVER) || defined(COCOA_OGL_DRIVER)

	case _hoops_IRGCP:
	case _hoops_PSSIP:
	case _hoops_SSSIP:
	case _hoops_RGGCP:
	case _hoops_IGGCP:
	case _hoops_RAGCP:{
		/*_hoops_ARHHC _hoops_PRHHC _hoops_HRHHC _hoops_AGIR _hoops_GCIAH [_hoops_HAICR,_hoops_SAHHC]_hoops_GPHHC[_hoops_RPHHC,_hoops_APHHC]_hoops_PPHHC[_hoops_HPHHC,_hoops_IPHHC]_hoops_CPHHC*/
		int _hoops_PGCRC = 0;

		if (matrix &&
			_hoops_ICHA &&
			matrix->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);

		if (ts->_hoops_HCHA)
			_hoops_CCIRC = false;

		j=0;
		if (dc->_hoops_CGHAR == null) {
			if (_hoops_CCIRC && ts->total >= _hoops_HGGHC) {
				ASSERT (!matrix);

				_hoops_CPPRC(_hoops_CSRGR);
				glVertexPointer(3, GL_FLOAT, 0, points);

				if (_hoops_CCHA) {
					ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,true);
					glTexCoordPointer(2, GL_FLOAT, _hoops_GSHA*sizeof(float), _hoops_CCHA);
				}

				if (_hoops_PCHA) {
					ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
					glColorPointer(3, GL_FLOAT, 0, _hoops_PCHA);
				}

				if (_hoops_ICHA) {
					_hoops_HGCRC(_hoops_CSRGR);
					glNormalPointer(GL_FLOAT, 0, _hoops_ICHA);
				}

				for (i = 0; i < _hoops_PHHA; i++) {
					if (lengths[i] < _hoops_CIIPP)
						_hoops_PGCRC += lengths[i] - 2;
					else
						glDrawElements(GL_TRIANGLE_STRIP, lengths[i], GL_UNSIGNED_INT, &_hoops_AIHA[j]);
					j += lengths[i];
				}
				if (_hoops_PGCRC) {
					int *_hoops_RGCRC, *_hoops_AGCRC;

					j = 0;
					if (!_hoops_CSRGR->_hoops_IHSGC)
						ALLOC_ARRAY(_hoops_CSRGR->_hoops_IHSGC, _hoops_CHSGC, int);
					_hoops_RGCRC = _hoops_CSRGR->_hoops_IHSGC;
					_hoops_AGCRC = _hoops_RGCRC;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_CIIPP) {
							if (_hoops_AGCRC - _hoops_RGCRC + (lengths[i]-2)*3 >= _hoops_CHSGC) {
								glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
								_hoops_AGCRC = _hoops_RGCRC;
							}
							_hoops_SAHAR = j+lengths[i];
							j += 2;
							while (j<_hoops_SAHAR) {
								*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
								*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
								*_hoops_AGCRC++ = _hoops_AIHA[ j ];
								j++;
								if (j == _hoops_SAHAR)
									break;
								*_hoops_AGCRC++ = _hoops_AIHA[ j ];
								*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
								*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
								j++;
							}
						}
						else
							j += lengths[i];
					}
					if (_hoops_AGCRC-_hoops_RGCRC > 0)
						glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
				}
				_hoops_AHPRC(_hoops_CSRGR);
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,false);
				_hoops_RHPRC(_hoops_CSRGR);
				_hoops_IGCRC(_hoops_CSRGR);
			}
			else {
				for (i = 0; i < _hoops_PHHA; i++) {
					if (!lengths) {
						_hoops_PGCRC++;
						j += 3;
					}
					else if (lengths[i] < _hoops_CIIPP) {
						_hoops_PGCRC += lengths[i] - 2;
						j += lengths[i];
					}
					else {
						glBegin (GL_TRIANGLE_STRIP);
						_hoops_SAHAR = j + lengths[i];
						while (j<_hoops_SAHAR) {
							_hoops_HCGS = _hoops_AIHA[j];
							if (_hoops_CSRGR->_hoops_SPGRC) {
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
							}
							else if (_hoops_CCHA) {
								glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
							}
							else if (ts->_hoops_HCHA) {
								glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
							}
							else if (_hoops_PCHA)
								glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
							if (matrix) {
								Vector _hoops_HIPCP, _hoops_IIPCP;
								_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HIPCP);
								if (_hoops_ICHA) {
									_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_IIPCP);
									_hoops_RRCRC (_hoops_RRIRC, _hoops_IIPCP, _hoops_HIPCP, _hoops_CSRGR->_hoops_SRIRC);
								}
								glVertex3fv (&_hoops_HIPCP.x);
							}
							else {
								if (_hoops_ICHA)
									_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
								glVertex3fv (&points[_hoops_HCGS].x);
							}
							j++;
						}
						glEnd ();
					}
				}
				if (_hoops_PGCRC) {
					int _hoops_IRHHC;
					Point xpts[4];
					Vector _hoops_SPHHC[4];
					j = 0;
					glBegin (GL_TRIANGLES);
					_hoops_HCGS = -1;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (!lengths || lengths[i] < _hoops_CIIPP) {
							if (lengths)
								_hoops_SAHAR = j+lengths[i];
							else
								_hoops_SAHAR = j + 3;
							j += 2;
							_hoops_IRHHC = 0;

							if (matrix) {
								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j-2];
								else
									_hoops_HCGS++;
								_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[0]);
								if (_hoops_ICHA)
									_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[0]);

								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j-1];
								else
									_hoops_HCGS++;
								_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[1]);
								if (_hoops_ICHA)
									_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[1]);
							}

							while (j<_hoops_SAHAR) {
								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j-2];
								else
									_hoops_HCGS++;
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
								}
								else if (_hoops_PCHA)
									glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[_hoops_IRHHC%4], xpts[_hoops_IRHHC%4], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&xpts[_hoops_IRHHC%4].x);
								}
								else  {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}

								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j-1];
								else
									_hoops_HCGS++;
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
								}
								else if (_hoops_PCHA)
									glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[(_hoops_IRHHC+1)%4], xpts[(_hoops_IRHHC+1)%4], _hoops_CSRGR->_hoops_SRIRC);
 									glVertex3fv (&xpts[(_hoops_IRHHC+1)%4].x);
								}
								else  {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}

								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j];
								else
									_hoops_HCGS++;
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
								}
								else if (_hoops_PCHA)
									glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
								if (matrix) {
									int ii = (_hoops_IRHHC+2)%4;
									_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[ii]);
									if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[ii]);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[ii], xpts[ii], _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&xpts[ii].x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}
								j++;
								_hoops_IRHHC++;
								if (j == _hoops_SAHAR)
									break;
								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j];
								else
									_hoops_HCGS++;
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
								}
								else if (_hoops_PCHA)
									glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
								if (matrix) {
									int ii = (_hoops_IRHHC+2)%4;
									_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[ii]);
									if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[ii]);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[ii], xpts[ii], _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&xpts[ii].x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}

								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j-1];
								else
									_hoops_HCGS++;
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
								}
								else if (_hoops_PCHA)
									glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[(_hoops_IRHHC+1)%4], xpts[(_hoops_IRHHC+1)%4], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&xpts[(_hoops_IRHHC+1)%4].x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}

								if (_hoops_AIHA)
									_hoops_HCGS = _hoops_AIHA[j-2];
								else
									_hoops_HCGS++;
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
								}
								else if (_hoops_PCHA)
									glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
								if (matrix) {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[_hoops_IRHHC%4], xpts[_hoops_IRHHC%4], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&xpts[_hoops_IRHHC%4].x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv (&points[_hoops_HCGS].x);
								}
								j++;
								_hoops_IRHHC++;
							}
						}
						else
							j += lengths[i];
					}
					glEnd ();
				}
			}
		}
		else {
			if (_hoops_CCIRC && ts->total >= _hoops_HGGHC) {
				/* _hoops_GRP _hoops_GPHA _hoops_SIRGR _hoops_PPR _hoops_GSSIA */
				ASSERT (!matrix);

				_hoops_CPPRC(_hoops_CSRGR);
				glVertexPointer(3, GL_FLOAT, 0, points);

				if (_hoops_CCHA) {
					ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,true);
					glTexCoordPointer(2, GL_FLOAT, _hoops_GSHA*sizeof(float), _hoops_CCHA);
				}

				if (_hoops_PCHA) {
					ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
					glColorPointer(3, GL_FLOAT, 0, _hoops_PCHA);
				}

				if (_hoops_ICHA) {
					_hoops_HGCRC(_hoops_CSRGR);
					glNormalPointer(GL_FLOAT, 0, _hoops_ICHA);
				}

				_hoops_SSPAR = 0;
				for (i = 0; i < _hoops_PHHA; i++) {
					_hoops_SAHAR = j + lengths[i];
					_hoops_PGGHC = _hoops_SSPAR + lengths[i] - 2;
					if (lengths[i] < _hoops_CIIPP) {
						_hoops_PGCRC += lengths[i] - 2;
					}
					else {
						_hoops_PGHAR = j;
						j += 2;
						if (face_indices)
							while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[face_indices[j]])
								j++;
						else {
							while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[_hoops_SSPAR]) {
								j++;
								_hoops_SSPAR++;
							}
						}
						if (j<_hoops_SAHAR) {
							/* _hoops_AHIC _hoops_HGPP _hoops_SGS _hoops_SR _hoops_IGHAR _hoops_RH _hoops_APRAR _hoops_SCGR _hoops_SCPH _hoops_PPR _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PCCP _hoops_PRGI _hoops_PHI _hoops_IIGR _hoops_HIPH */
							if ((j-_hoops_PGHAR) & 0x1) {
								_hoops_SSPAR--;
								j -= 3;
							}
							else
								j -= 2;
							end = _hoops_SAHAR;
							if (face_indices) {
								while (!dc->_hoops_CGHAR[face_indices[end-1]])
									end--;
							}
							else {
								k = 1;
								while (!dc->_hoops_CGHAR[_hoops_PGGHC-k])
									k++;
								end -= k-1;
							}
							glDrawElements(GL_TRIANGLE_STRIP, end-j, GL_UNSIGNED_INT, &_hoops_AIHA[j]);
						}
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
				if (_hoops_PGCRC) {
					int *_hoops_RGCRC, *_hoops_AGCRC;

					j = 0;
					if (!_hoops_CSRGR->_hoops_IHSGC)
						ALLOC_ARRAY(_hoops_CSRGR->_hoops_IHSGC, _hoops_CHSGC, int);
					_hoops_RGCRC = _hoops_CSRGR->_hoops_IHSGC;
					_hoops_AGCRC = _hoops_RGCRC;
					_hoops_SSPAR = 0;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_CIIPP) {
							if (_hoops_AGCRC - _hoops_RGCRC + (lengths[i]-2)*3 >= _hoops_CHSGC) {
								glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
								_hoops_AGCRC = _hoops_RGCRC;
							}
							_hoops_SAHAR = j+lengths[i];
							j += 2;
							if (face_indices) {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									}
									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
									}
									j++;
								}
							}
							else {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
									}
									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										*_hoops_AGCRC++ = _hoops_AIHA[ j ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-1 ];
										*_hoops_AGCRC++ = _hoops_AIHA[ j-2 ];
									}
									j++;
								}
							}
						}
						else {
							j += lengths[i];
							_hoops_SSPAR += lengths[i] - 2;
						}
					}
					if (_hoops_AGCRC-_hoops_RGCRC > 0)
						glDrawElements(GL_TRIANGLES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
				}
				_hoops_AHPRC(_hoops_CSRGR);
				_hoops_RHPRC(_hoops_CSRGR);
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,false);
				_hoops_IGCRC(_hoops_CSRGR);
			}
			else {
				/* _hoops_GRAA-_hoops_GPHA _hoops_CRPR, _hoops_CCA _hoops_GSSIA */
				_hoops_SSPAR = 0;
				for (i = 0; i < _hoops_PHHA; i++) {
					if (lengths[i] < _hoops_CIIPP) {
						_hoops_PGCRC += lengths[i] - 2;
						j += lengths[i];
						_hoops_SSPAR += lengths[i]-2;
						continue;
					}
					_hoops_SAHAR = j + lengths[i];
					_hoops_PGGHC = _hoops_SSPAR + lengths[i]-2;
					_hoops_PGHAR = j;
					j += 2;
					if (face_indices) {
						while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[face_indices[j]])
							j++;
					}
					else {
						while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[_hoops_SSPAR]) {
							j++;
							_hoops_SSPAR++;
						}
					}
					if (j<_hoops_SAHAR) {
						end = _hoops_SAHAR;
						if (face_indices) {
							while (!dc->_hoops_CGHAR[face_indices[end-1]])
								end--;
						}
						else {
							k = 1;
							while (!dc->_hoops_CGHAR[_hoops_PGGHC-k])
								k++;
							end -= k-1;
						}
						if ((j-_hoops_PGHAR) & 0x1) {
							_hoops_SSPAR--;
							j -= 3;
						}
						else
							j -= 2;
						glBegin (GL_TRIANGLE_STRIP);
						while (j < end) {
							_hoops_HCGS = _hoops_AIHA[j];
							if (_hoops_CSRGR->_hoops_SPGRC) {
								(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
							}
							else if (_hoops_CCHA) {
								glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
							}
							else if (ts->_hoops_HCHA) {
								glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
							}
							else if (_hoops_PCHA)
								glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
							if (matrix) {
								Vector _hoops_HIPCP, _hoops_IIPCP;
								_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HIPCP);
								if (_hoops_ICHA) {
									_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_IIPCP);
									_hoops_RRCRC (_hoops_RRIRC, _hoops_IIPCP, _hoops_HIPCP, _hoops_CSRGR->_hoops_SRIRC);
								}
								glVertex3fv (&_hoops_HIPCP.x);
							}
							else {
								if (_hoops_ICHA)
									_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
								glVertex3fv (&points[_hoops_HCGS].x);
							}
							j++;
						}
						glEnd ();
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
				if (_hoops_PGCRC) {
					int _hoops_IRHHC;
					Point xpts[4];
					Point _hoops_SPHHC[4];
					j = 0;
					glBegin (GL_TRIANGLES);
					_hoops_SSPAR=0;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_CIIPP) {
							_hoops_SAHAR = j+lengths[i];
							j += 2;
							_hoops_IRHHC = 0;

							if (face_indices)  {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										if (matrix && !_hoops_IRHHC) {
											_hoops_HCGS = _hoops_AIHA[j-2];
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[0]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[0]);

											_hoops_HCGS = _hoops_AIHA[j-1];
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[1]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[1]);
										}

										_hoops_HCGS = _hoops_AIHA[j-2];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[_hoops_IRHHC%4], xpts[_hoops_IRHHC%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[_hoops_IRHHC%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j-1];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[(_hoops_IRHHC+1)%4], xpts[(_hoops_IRHHC+1)%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[(_hoops_IRHHC+1)%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											int ii = (_hoops_IRHHC+2)%4;
											_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[ii]);
											if (_hoops_ICHA) {
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[ii]);
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[ii], xpts[ii], _hoops_CSRGR->_hoops_SRIRC);
											}
											glVertex3fv (&xpts[ii].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}
										_hoops_IRHHC++;
									}
									else
										_hoops_IRHHC = 0;

									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[face_indices[j]]) {
										if (matrix && !_hoops_IRHHC) {
											_hoops_HCGS = _hoops_AIHA[j-2];
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[0]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[0]);

											_hoops_HCGS = _hoops_AIHA[j-1];
											_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[1]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[1]);
										}

										_hoops_HCGS = _hoops_AIHA[j];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											int ii = (_hoops_IRHHC+2)%4;
											_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[ii]);
											if (_hoops_ICHA) {
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[ii]);
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[ii], xpts[ii], _hoops_CSRGR->_hoops_SRIRC);
											}
											glVertex3fv (&xpts[ii].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j-1];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[(_hoops_IRHHC+1)%4], xpts[(_hoops_IRHHC+1)%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[(_hoops_IRHHC+1)%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j-2];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[_hoops_IRHHC%4], xpts[_hoops_IRHHC%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[_hoops_IRHHC%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}
										_hoops_IRHHC++;
									}
									else
										_hoops_IRHHC = 0;
									j++;
								}
							}
							else {
								while (j<_hoops_SAHAR) {
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										if (matrix && !_hoops_IRHHC) {
											_hoops_HCGS = _hoops_AIHA[j-2];
											_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[0]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[0]);

											_hoops_HCGS = _hoops_AIHA[j-1];
											_hoops_SGCRC (matrix,points[_hoops_HCGS],xpts[1]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[1]);
										}

										_hoops_HCGS = _hoops_AIHA[j-2];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[_hoops_IRHHC%4], xpts[_hoops_IRHHC%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[_hoops_IRHHC%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j-1];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[(_hoops_IRHHC+1)%4], xpts[(_hoops_IRHHC+1)%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[(_hoops_IRHHC+1)%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											int ii = (_hoops_IRHHC+2)%4;
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[ii]);
											if (_hoops_ICHA) {
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[ii]);
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[ii], xpts[ii], _hoops_CSRGR->_hoops_SRIRC);
											}
											glVertex3fv (&xpts[ii].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}
										_hoops_IRHHC++;
									}
									else
										_hoops_IRHHC = 0;

									j++;
									if (j == _hoops_SAHAR)
										break;
									if (dc->_hoops_CGHAR[_hoops_SSPAR++]) {
										if (matrix && !_hoops_IRHHC) {
											_hoops_HCGS = _hoops_AIHA[j-2];
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[0]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[0]);

											_hoops_HCGS = _hoops_AIHA[j-1];
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[1]);
											if (_hoops_ICHA)
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[1]);
										}

										_hoops_HCGS = _hoops_AIHA[j];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else  if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											int ii = (_hoops_IRHHC+2)%4;
											_hoops_SGCRC (matrix, points[_hoops_HCGS], xpts[ii]);
											if (_hoops_ICHA) {
												_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_SPHHC[ii]);
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[ii], xpts[ii], _hoops_CSRGR->_hoops_SRIRC);
											}
											glVertex3fv (&xpts[ii].x);
										}
										else  {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j-1];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix)  {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[(_hoops_IRHHC+1)%4], xpts[(_hoops_IRHHC+1)%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[(_hoops_IRHHC+1)%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}

										_hoops_HCGS = _hoops_AIHA[j-2];
										if (_hoops_CSRGR->_hoops_SPGRC) {
											(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
											(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &ts->_hoops_GSSH->_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
										}
										else if (_hoops_CCHA) {
											glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
										}
										else if (ts->_hoops_HCHA) {
											glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
										}
										else if (_hoops_PCHA)
											glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
										if (matrix) {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_SPHHC[_hoops_IRHHC%4], xpts[_hoops_IRHHC%4], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&xpts[_hoops_IRHHC%4].x);
										}
										else {
											if (_hoops_ICHA)
												_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
											glVertex3fv (&points[_hoops_HCGS].x);
										}
										_hoops_IRHHC++;
									}
									else
										_hoops_IRHHC = 0;
									j++;
								}
							}
						}
						else {
							j += lengths[i];
							_hoops_SSPAR += lengths[i] - 2;
						}
					}
					glEnd ();
				}
			}
		}
	} break;
#endif

