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
 * $Id: obf_tmp.txt 1.26 2010-11-30 20:12:24 heppe Exp $
 *
 * This file contains the cases from draw_3d_tristrip that have any face
 * attributes (i.e. FC and/or FN).
 */

#if defined(GLX_DRIVER) || defined(WGL_DRIVER) || defined(AGL_DRIVER) || defined(COCOA_OGL_DRIVER)
	case _hoops_ISSIP:
	case _hoops_PGGCP:
	case _hoops_SGGCP:
	case _hoops_RRGCP:
	case _hoops_PRGCP:
	case _hoops_SRGCP: {
		/* _hoops_ARHHC _hoops_PRHHC _hoops_HRHHC _hoops_RRGR _hoops_GCIAH _hoops_HCR _hoops_ARAR _hoops_SGS _hoops_HS _hoops_HSP _hoops_AIRC */
		int n=0;
		int _hoops_PGCRC = 0;
		int length;
		int _hoops_IRHHC;
		_hoops_ARPA _hoops_CRHHC;
		Vector _hoops_SRHHC;
		Point _hoops_HSHSA;
		bool _hoops_CRSPH;
		_hoops_GRA const &_hoops_RRA = nr->_hoops_ARA;

		_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

		if (matrix &&
			(_hoops_PRHH || _hoops_ICHA) &&
			matrix->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);

		//_hoops_RPP (_hoops_HGPGA->_hoops_IHAH._hoops_GAHHC)
		//	_hoops_PRGHC = _hoops_HGPGA->_hoops_ASHGC->_hoops_SGGHC;
		//_hoops_SHS
		//	_hoops_PRGHC = _hoops_HGPGA->_hoops_ASHGC->_hoops_ARGHC;
		_hoops_CIIPP = 0x7fffffff;

		/* _hoops_HAIA _hoops_IRSP _hoops_IIGR _hoops_GCGAH'_hoops_GRI _hoops_RAHHC _hoops_AAHHC _hoops_SPSIR _hoops_AHGS _hoops_IS _hoops_HS _hoops_SPGC _hoops_GHGA
			_hoops_GPIC _hoops_RCA _hoops_GRP _hoops_GPHA _hoops_SIRGR */
		if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_FLAT_VERTEX_ARRAYS))
			_hoops_CCIRC = false;
		if (_hoops_CRSPH && (_hoops_PAGI || _hoops_PCHA))
			_hoops_CCIRC = false;
		if (ts->_hoops_HCHA != null)
			_hoops_CCIRC = false;


		j=0;
		_hoops_IRHHC = 0;
		if (_hoops_CCIRC && ts->total >= _hoops_HGGHC) {

			ASSERT (!matrix);

			if (_hoops_CCHA) {
				if (!_hoops_CSRGR->_hoops_AISGC) {
					ALLOC_ARRAY (_hoops_CSRGR->_hoops_AISGC,
								 2*OGL_SCRATCH_SPACE_SIZE,
								 float);
				}
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,true);
				glTexCoordPointer(2, GL_FLOAT, 0, _hoops_CSRGR->_hoops_AISGC);
			}
			else
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,false);
			if (_hoops_PAGI || _hoops_PCHA) {
				if (!_hoops_CSRGR->_hoops_RISGC)
					ALLOC_ARRAY(_hoops_CSRGR->_hoops_RISGC, OGL_SCRATCH_SPACE_SIZE, RGB);
				ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
				glColorPointer(3, GL_FLOAT, 0, _hoops_CSRGR->_hoops_RISGC);
			}
			else
				_hoops_RHPRC(_hoops_CSRGR);
			if (_hoops_PRHH || _hoops_ICHA) {
				if (!_hoops_CSRGR->_hoops_GISGC)
					ALLOC_ARRAY(_hoops_CSRGR->_hoops_GISGC, OGL_SCRATCH_SPACE_SIZE, Vector);
				_hoops_HGCRC(_hoops_CSRGR);
				glNormalPointer(GL_FLOAT, 0, _hoops_CSRGR->_hoops_GISGC);
			}
			else
				_hoops_IGCRC(_hoops_CSRGR);
			if (!_hoops_CSRGR->_hoops_SHSGC)
				ALLOC_ARRAY(_hoops_CSRGR->_hoops_SHSGC, OGL_SCRATCH_SPACE_SIZE, Point);
			_hoops_CPPRC(_hoops_CSRGR);
			glVertexPointer(3, GL_FLOAT, 0, _hoops_CSRGR->_hoops_SHSGC);

			if (_hoops_PRHA ||
				(rc->_hoops_CHRRC > 1 && XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_FLAT_TRISTRIP_MISMATCH))) {
				/* _hoops_ARP _hoops_IRS _hoops_CPPPR _hoops_CHPP _hoops_GCSRP _hoops_IS _hoops_HSPAA _hoops_PAHHC (_hoops_IAS._hoops_ISHI. _hoops_RHI _hoops_SIA) _hoops_ARAR _hoops_ISHP _hoops_RH
					_hoops_HIPH _hoops_CRAA _hoops_PGGA _hoops_SSIA _hoops_PPPPR'_hoops_RA _hoops_HS _hoops_HAHHC _hoops_IGSGR _hoops_SARR */
				_hoops_CIIPP = 0x7fffffff;
				_hoops_PGCRC = ts->total;
			}
			else {
				_hoops_SSPAR = 0;
				for (i=0; i<_hoops_PHHA; i++) {
					n=0;
					length = lengths[i];
					_hoops_SAHAR = j + length;
					_hoops_PGGHC = _hoops_SSPAR + length - 2;
					if (length < _hoops_CIIPP) {
						_hoops_PGCRC += length - 2;
					}
					else {
						if (dc->_hoops_CGHAR) {
							_hoops_PGHAR = j;
							j += 2;
							/* _hoops_CCPH _hoops_HII _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_CGGR */
							if (face_indices)
								while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[face_indices[j]])
									j++;
							else {
								k = 0;
								while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[_hoops_SSPAR + k]) {
									j++;
									k++;
								}
							}
							if (j == _hoops_SAHAR) {
								_hoops_SSPAR = _hoops_PGGHC;
								continue; /* _hoops_RH _hoops_RSIR _hoops_CGGR _hoops_HRGR _hoops_HPPHR _hoops_RHGCP.  _hoops_PHHR _hoops_IS _hoops_SPS _hoops_HAS */
							}
							if (lengths[i] > 0) {
								/* _hoops_AHIC _hoops_HGPP _hoops_SGS _hoops_SR _hoops_IGHAR _hoops_RH _hoops_APRAR _hoops_SCGR _hoops_SCPH _hoops_PPR _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PCCP _hoops_PRGI _hoops_PHI _hoops_IIGR _hoops_HIPH */
								if ((j-_hoops_PGHAR) & 0x1)
									j -= 3;
								else
									j -= 2;
							}
							else
								j = _hoops_PGHAR; /* _hoops_RPP _hoops_HAR _hoops_AGIRH _hoops_RHGCP, _hoops_IAHHC _hoops_PAH _hoops_RGAR _hoops_CCPH _hoops_HII _hoops_RH _hoops_RSGR */
							end = _hoops_SAHAR;
							/* _hoops_CCPH _hoops_HII _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_CGGR */
							if (face_indices) {
								while (!dc->_hoops_CGHAR[face_indices[end-1]])
									end--;
							}
							else {
								k = 1;
								while (!dc->_hoops_CGHAR[_hoops_PGGHC-k])
									k++;
								end -= k-1;
								_hoops_SSPAR += j - _hoops_PGHAR;
							}
						}
						else
							end = _hoops_SAHAR;

						if (face_indices)
							_hoops_SSPAR = face_indices[j+2];
						if (_hoops_PRHH) {
							_hoops_GCHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n]);
							_hoops_CSRGR->_hoops_GISGC[n+1] = _hoops_CSRGR->_hoops_GISGC[n];
							_hoops_CSRGR->_hoops_GISGC[n+2] = _hoops_CSRGR->_hoops_GISGC[n];
						}
						if (_hoops_PAGI) {
							_hoops_CSRGR->_hoops_RISGC[n]   = _hoops_PAGI[_hoops_SSPAR];
							_hoops_CSRGR->_hoops_RISGC[n+1] = _hoops_PAGI[_hoops_SSPAR];
							_hoops_CSRGR->_hoops_RISGC[n+2] = _hoops_PAGI[_hoops_SSPAR];
						}
						/* _hoops_RPP _hoops_SR _hoops_HS _hoops_GPHA _hoops_AIRC, _hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_GGR _hoops_HAHHC _hoops_IGSGR _hoops_SARR */
						ASSERT(!_hoops_CCHA && !_hoops_PCHA && !_hoops_ICHA);
						_hoops_CSRGR->_hoops_SHSGC[n] = points[_hoops_AIHA[j]];
						j++; n++;
						_hoops_CSRGR->_hoops_SHSGC[n] = points[_hoops_AIHA[j]];
						j++; n++;
						while (j < end) {
							_hoops_CSRGR->_hoops_SHSGC[n] = points[_hoops_AIHA[j]];
							if (face_indices)
								_hoops_SSPAR = face_indices[j];
							if (_hoops_PRHH)
								_hoops_GCHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n]);
							if (_hoops_PAGI)
								_hoops_CSRGR->_hoops_RISGC[n] = _hoops_PAGI[_hoops_SSPAR];
							j++; n++;

							if (n == OGL_SCRATCH_SPACE_SIZE) {
								/* _hoops_AACC _hoops_PSAP _hoops_RH _hoops_SCGR _hoops_CGGR _hoops_PPR _hoops_HSPP _hoops_IRS _hoops_CCAH _hoops_SPR.  (_hoops_IGIPR _hoops_CAHHC _hoops_HRGR _hoops_PRGI) */
								glDrawArrays(GL_TRIANGLE_STRIP, 0, n);
								n = 0;
								j -= 2;
								if (_hoops_PRHH) {
									_hoops_GCHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n]);
									_hoops_CSRGR->_hoops_GISGC[n+1] = _hoops_CSRGR->_hoops_GISGC[n];
									_hoops_CSRGR->_hoops_GISGC[n+2] = _hoops_CSRGR->_hoops_GISGC[n];
								}
								if (_hoops_PAGI) {
									_hoops_CSRGR->_hoops_RISGC[n+0] = _hoops_PAGI[_hoops_SSPAR];
									_hoops_CSRGR->_hoops_RISGC[n+1] = _hoops_PAGI[_hoops_SSPAR];
									_hoops_CSRGR->_hoops_RISGC[n+2] = _hoops_PAGI[_hoops_SSPAR];
								}
								_hoops_CSRGR->_hoops_SHSGC[n] = points[_hoops_AIHA[j]];
								j++; n++;
								_hoops_CSRGR->_hoops_SHSGC[n] = points[_hoops_AIHA[j]];
								j++; n++;
							}
							if (!face_indices)
								_hoops_SSPAR++;
						}
						if (lengths[i] > 0)
							glDrawArrays(GL_TRIANGLE_STRIP, 0, n);
						else
							glDrawArrays(GL_TRIANGLE_FAN, 0, n);
						n = 0;
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
			}
			if (_hoops_PGCRC) {
				_hoops_SSPAR = -1;
				n=0;
				j=0;
				for (i=0; i<_hoops_PHHA; i++) {
					_hoops_SAHAR = j + lengths[i];
					_hoops_PGGHC = _hoops_SSPAR + lengths[i] - 2;
					if (lengths[i] < _hoops_CIIPP) {
						j += 2;
						while (j < _hoops_SAHAR) {
							if (n + 6 >= OGL_SCRATCH_SPACE_SIZE) {
								glDrawArrays(GL_TRIANGLES,0,n);
								n = 0;
							}
							if (face_indices)
								_hoops_SSPAR = face_indices[j];
							else
								_hoops_SSPAR++;
							if (!dc->_hoops_CGHAR || dc->_hoops_CGHAR[_hoops_SSPAR]) {
								if (_hoops_PRHH) {
									_hoops_GCHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n]);
									_hoops_CSRGR->_hoops_GISGC[n+1] = _hoops_CSRGR->_hoops_GISGC[n];
									_hoops_CSRGR->_hoops_GISGC[n+2] = _hoops_CSRGR->_hoops_GISGC[n];
								}
								else if (_hoops_ICHA) {
									_hoops_SIHAC (_hoops_RRIRC, _hoops_ICHA[_hoops_AIHA[j-2]], points[_hoops_AIHA[j-2]], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n+0]);
									_hoops_SIHAC (_hoops_RRIRC, _hoops_ICHA[_hoops_AIHA[j-1]], points[_hoops_AIHA[j-1]], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n+1]);
									_hoops_SIHAC (_hoops_RRIRC, _hoops_ICHA[_hoops_AIHA[j-0]], points[_hoops_AIHA[j-0]], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n+2]);
								}
								if (_hoops_CCHA) {
									_hoops_AIGA(&_hoops_CCHA[_hoops_GSHA*_hoops_AIHA[j-2]], 2, float, &_hoops_CSRGR->_hoops_AISGC[(n+0)*2]);
									_hoops_AIGA(&_hoops_CCHA[_hoops_GSHA*_hoops_AIHA[j-1]], 2, float, &_hoops_CSRGR->_hoops_AISGC[(n+1)*2]);
									_hoops_AIGA(&_hoops_CCHA[_hoops_GSHA*_hoops_AIHA[j-0]], 2, float, &_hoops_CSRGR->_hoops_AISGC[(n+2)*2]);
								}
								if (_hoops_PAGI) {
									_hoops_CSRGR->_hoops_RISGC[n+0] = _hoops_PAGI[_hoops_SSPAR];
									_hoops_CSRGR->_hoops_RISGC[n+1] = _hoops_PAGI[_hoops_SSPAR];
									_hoops_CSRGR->_hoops_RISGC[n+2] = _hoops_PAGI[_hoops_SSPAR];
								}
								else if (_hoops_PCHA) {
									_hoops_CSRGR->_hoops_RISGC[n+0] = _hoops_PCHA[_hoops_AIHA[j-2]];
									_hoops_CSRGR->_hoops_RISGC[n+1] = _hoops_PCHA[_hoops_AIHA[j-1]];
									_hoops_CSRGR->_hoops_RISGC[n+2] = _hoops_PCHA[_hoops_AIHA[j-0]];
								}
								_hoops_CSRGR->_hoops_SHSGC[n+0] = points[_hoops_AIHA[j-2]];
								_hoops_CSRGR->_hoops_SHSGC[n+1] = points[_hoops_AIHA[j-1]];
								_hoops_CSRGR->_hoops_SHSGC[n+2] = points[_hoops_AIHA[j-0]];
								n += 3;
							}
							j++;
							if (j == _hoops_SAHAR)
								break;
							if (face_indices)
								_hoops_SSPAR = face_indices[j];
							else
								_hoops_SSPAR++;
							if (!dc->_hoops_CGHAR || dc->_hoops_CGHAR[_hoops_SSPAR]) {
								if (_hoops_PRHH) {
									_hoops_GCHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n]);
									_hoops_CSRGR->_hoops_GISGC[n+1] = _hoops_CSRGR->_hoops_GISGC[n];
									_hoops_CSRGR->_hoops_GISGC[n+2] = _hoops_CSRGR->_hoops_GISGC[n];
								}
								else if (_hoops_ICHA) {
									_hoops_SIHAC (_hoops_RRIRC, _hoops_ICHA[_hoops_AIHA[j-1]], points[_hoops_AIHA[j-1]], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n+0]);
									_hoops_SIHAC (_hoops_RRIRC, _hoops_ICHA[_hoops_AIHA[j-2]], points[_hoops_AIHA[j-2]], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n+1]);
									_hoops_SIHAC (_hoops_RRIRC, _hoops_ICHA[_hoops_AIHA[j-0]], points[_hoops_AIHA[j-0]], _hoops_CSRGR->_hoops_SRIRC, _hoops_CSRGR->_hoops_GISGC[n+2]);
								}
								if (_hoops_CCHA) {
									_hoops_AIGA(&_hoops_CCHA[_hoops_GSHA*_hoops_AIHA[j-1]], 2, float, &_hoops_CSRGR->_hoops_AISGC[(n+0)*2]);
									_hoops_AIGA(&_hoops_CCHA[_hoops_GSHA*_hoops_AIHA[j-2]], 2, float, &_hoops_CSRGR->_hoops_AISGC[(n+1)*2]);
									_hoops_AIGA(&_hoops_CCHA[_hoops_GSHA*_hoops_AIHA[j-0]], 2, float, &_hoops_CSRGR->_hoops_AISGC[(n+2)*2]);
								}
								if (_hoops_PAGI) {
									_hoops_CSRGR->_hoops_RISGC[n+0] = _hoops_PAGI[_hoops_SSPAR];
									_hoops_CSRGR->_hoops_RISGC[n+1] = _hoops_PAGI[_hoops_SSPAR];
									_hoops_CSRGR->_hoops_RISGC[n+2] = _hoops_PAGI[_hoops_SSPAR];
								}
								else if (_hoops_PCHA) {
									_hoops_CSRGR->_hoops_RISGC[n+0] = _hoops_PCHA[_hoops_AIHA[j-1]];
									_hoops_CSRGR->_hoops_RISGC[n+1] = _hoops_PCHA[_hoops_AIHA[j-2]];
									_hoops_CSRGR->_hoops_RISGC[n+2] = _hoops_PCHA[_hoops_AIHA[j-0]];
								}
								_hoops_CSRGR->_hoops_SHSGC[n+0] = points[_hoops_AIHA[j-1]];
								_hoops_CSRGR->_hoops_SHSGC[n+1] = points[_hoops_AIHA[j-2]];
								_hoops_CSRGR->_hoops_SHSGC[n+2] = points[_hoops_AIHA[j-0]];
								n += 3;
							}
							j++;
						}
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
				if (n != 0) {
					glDrawArrays(GL_TRIANGLES,0,n);
					n = 0;
				}
			}
			ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,0,false);
			_hoops_RHPRC(_hoops_CSRGR);
			_hoops_IGCRC(_hoops_CSRGR);
			_hoops_AHPRC(_hoops_CSRGR);
		}
		else {
			/* _hoops_GRAA-_hoops_GPHA _hoops_CRPR _hoops_AGIR */
			if (_hoops_PRHA) {
				/* _hoops_ARP _hoops_IRS _hoops_CPPPR _hoops_CHPP _hoops_GCSRP _hoops_IS _hoops_HSPAA _hoops_PAHHC (_hoops_IAS._hoops_ISHI. _hoops_RHI _hoops_SIA) _hoops_ARAR _hoops_ISHP _hoops_RH
					_hoops_HIPH _hoops_CRAA _hoops_PGGA _hoops_SSIA _hoops_PPPPR'_hoops_RA _hoops_HS _hoops_HAHHC _hoops_IGSGR _hoops_SARR */
				_hoops_CIIPP = 0x7fffffff;
				_hoops_PGCRC = ts->total;
			}
			else {
				_hoops_SSPAR = 0;
				for (i=0; i<_hoops_PHHA; i++) {
					length = lengths[i]; /* _hoops_IRS _hoops_SCPH _hoops_CGGR */
					_hoops_SAHAR = j + length;
					_hoops_PGGHC = _hoops_SSPAR + length - 2;
					if (length < _hoops_CIIPP) {
						_hoops_PGCRC += length - 2;
					}
					else {
						if (dc->_hoops_CGHAR) {
							_hoops_PGHAR = j;
							j += 2;
							_hoops_IRHHC = 0;

							/* _hoops_CCPH _hoops_HII _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_CGGR */
							if (face_indices)
								while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[face_indices[j]])
									j++;
							else {
								k = 0;
								while (j<_hoops_SAHAR && !dc->_hoops_CGHAR[_hoops_SSPAR + k]) {
									j++;
									k++;
								}
							}
							if (j == _hoops_SAHAR) {
								_hoops_SSPAR = _hoops_PGGHC;
								continue; /* _hoops_RH _hoops_RSIR _hoops_CGGR _hoops_HRGR _hoops_HPPHR _hoops_RHGCP.  _hoops_PHHR _hoops_IS _hoops_SPS _hoops_HAS */
							}
							if (lengths[i] > 0) {
								/* _hoops_AHIC _hoops_HGPP _hoops_SGS _hoops_SR _hoops_IGHAR _hoops_RH _hoops_APRAR _hoops_SCGR _hoops_SCPH _hoops_PPR _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PCCP _hoops_PRGI _hoops_PHI _hoops_IIGR _hoops_HIPH */
								if ((j-_hoops_PGHAR) & 0x1)
									j -= 3;
								else
									j -= 2;
							}
							else {
								/* _hoops_RPP _hoops_HAR _hoops_AGIRH _hoops_RHGCP, _hoops_IAHHC _hoops_PAH _hoops_RGAR _hoops_CCPH _hoops_HII _hoops_RH _hoops_RSGR */
								j = _hoops_PGHAR;
							}
							end = _hoops_SAHAR;
							/* _hoops_CCPH _hoops_HII _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_CGGR */
							if (face_indices) {
								while (!dc->_hoops_CGHAR[face_indices[end-1]])
									end--;
							}
							else {
								k = 1;
								while (!dc->_hoops_CGHAR[_hoops_PGGHC-k])
									k++;
								end -= k-1;
								_hoops_SSPAR += j - _hoops_PGHAR;
							}
						}
						else {
							end = _hoops_SAHAR;
						}

						glBegin(GL_TRIANGLE_STRIP);
						/* _hoops_RPP _hoops_SR _hoops_HS _hoops_GPHA _hoops_AIRC, _hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_GGR _hoops_HAHHC _hoops_IGSGR _hoops_SARR */
						ASSERT(!_hoops_CCHA && !_hoops_PCHA && !_hoops_ICHA);
						if (face_indices)
							_hoops_SSPAR = face_indices[j+2];
						if (_hoops_PAGI)
							_hoops_PSPAC  (&_hoops_PAGI[_hoops_SSPAR].red, _hoops_CRSPH);
						if (matrix) {
							int ii;
							if (_hoops_PRHH) {
								_hoops_GIRAC (matrix, _hoops_PRHH[_hoops_SSPAR], _hoops_CRHHC);
								_hoops_CIHAC (_hoops_RRIRC, _hoops_CRHHC, _hoops_CSRGR->_hoops_SRIRC);
							}
							for (ii = 0 ; ii < 3 ; ii++) {
								_hoops_SGCRC (matrix, points[_hoops_AIHA[j]], _hoops_HSHSA);
								glVertex3fv(&_hoops_HSHSA.x);
								j++;
							}
						}
						else {
							if (_hoops_PRHH)
								_hoops_CIHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
							glVertex3fv(&points[_hoops_AIHA[j++]].x);
							glVertex3fv(&points[_hoops_AIHA[j++]].x);
							glVertex3fv(&points[_hoops_AIHA[j++]].x);
						}
						while (j < end) {
							if (face_indices)
								_hoops_SSPAR = face_indices[j];
							else
								_hoops_SSPAR++;

							if (_hoops_PAGI)
								_hoops_PSPAC (&_hoops_PAGI[_hoops_SSPAR].red, _hoops_CRSPH);
							if (matrix) {
								if (_hoops_PRHH) {
									_hoops_GIRAC (matrix, _hoops_PRHH[_hoops_SSPAR], _hoops_CRHHC);
									_hoops_CIHAC (_hoops_RRIRC, _hoops_CRHHC, _hoops_CSRGR->_hoops_SRIRC);
								}
								_hoops_SGCRC (matrix, points[_hoops_AIHA[j]], _hoops_HSHSA);
								glVertex3fv(&_hoops_HSHSA.x);
							}
							else {
								if (_hoops_PRHH)
									_hoops_CIHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
								glVertex3fv(&points[_hoops_AIHA[j]].x);
							}
							j++;
						}
						glEnd();
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
			}
			if (_hoops_PGCRC) {
				_hoops_SSPAR = -1;
				n=0;
				j=0;
				glBegin(GL_TRIANGLES);
				for (i=0; i<_hoops_PHHA; i++) {
					_hoops_SAHAR = j + lengths[i];
					_hoops_PGGHC = _hoops_SSPAR + lengths[i] - 2;
					if (lengths[i] < _hoops_CIIPP) {
						j += 2;
						while (j < _hoops_SAHAR) {
							if (face_indices)
								_hoops_SSPAR = face_indices[j];
							else
								_hoops_SSPAR++;
							if (!dc->_hoops_CGHAR || dc->_hoops_CGHAR[_hoops_SSPAR]) {

								_hoops_HCGS = _hoops_AIHA[j];
								if (_hoops_PAGI)
									_hoops_PSPAC (&_hoops_PAGI[_hoops_SSPAR].red, _hoops_CRSPH);
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate);
								}

								if (_hoops_PCHA)
									glColor3fv(&_hoops_PCHA[_hoops_HCGS].red);
								if (matrix) {
									_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HSHSA);
									if (_hoops_PRHH) {
										_hoops_GIRAC (matrix, _hoops_PRHH[_hoops_SSPAR], _hoops_CRHHC);
										_hoops_CIHAC (_hoops_RRIRC, _hoops_CRHHC, _hoops_CSRGR->_hoops_SRIRC);
									}
									else if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], _hoops_HSHSA, _hoops_SRHHC);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SRHHC, _hoops_HSHSA, _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&_hoops_HSHSA.x);
								}
								else {
									if (_hoops_PRHH)
										_hoops_CIHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
									else if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv(&points[_hoops_HCGS].x);
								}

								_hoops_HCGS = _hoops_AIHA[j-2];
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate);
								}
								if (_hoops_PCHA)
									glColor3fv(&_hoops_PCHA[_hoops_HCGS].red);
								if (matrix) {
									_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HSHSA);
									if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], _hoops_HSHSA, _hoops_SRHHC);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SRHHC, _hoops_HSHSA, _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&_hoops_HSHSA.x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv(&points[_hoops_HCGS].x);
								}

								_hoops_HCGS = _hoops_AIHA[j-1];
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate);
								}
								if (_hoops_PCHA)
									glColor3fv(&_hoops_PCHA[_hoops_HCGS].red);
								if (matrix) {
									_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HSHSA);
									if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], _hoops_HSHSA, _hoops_SRHHC);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SRHHC, _hoops_HSHSA, _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&_hoops_HSHSA.x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv(&points[_hoops_HCGS].x);
								}
								_hoops_IRHHC++;
							}
							else
								_hoops_IRHHC = 0;
							j++;
							if (j == _hoops_SAHAR)
								break;
							if (face_indices)
								_hoops_SSPAR = face_indices[j];
							else
								_hoops_SSPAR++;
							if (!dc->_hoops_CGHAR || dc->_hoops_CGHAR[_hoops_SSPAR]) {
								_hoops_HCGS = _hoops_AIHA[j];
								if (_hoops_PAGI)
									_hoops_PSPAC (&_hoops_PAGI[_hoops_SSPAR].red, _hoops_CRSPH);
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate);
								}
								if (_hoops_PCHA)
									glColor3fv(&_hoops_PCHA[_hoops_HCGS].red);
								if (matrix) {
									_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HSHSA);
									if (_hoops_PRHH) {
										_hoops_GIRAC (matrix, _hoops_PRHH[_hoops_SSPAR], _hoops_CRHHC);
										_hoops_CIHAC (_hoops_RRIRC, _hoops_CRHHC, _hoops_CSRGR->_hoops_SRIRC);
									}
									else if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], _hoops_HSHSA, _hoops_SRHHC);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SRHHC, _hoops_HSHSA, _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&_hoops_HSHSA.x);
								}
								else {
									if (_hoops_PRHH)
										_hoops_CIHAC (_hoops_RRIRC, _hoops_PRHH[_hoops_SSPAR], _hoops_CSRGR->_hoops_SRIRC);
									else if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv(&points[_hoops_HCGS].x);
								}

								_hoops_HCGS = _hoops_AIHA[j-1];
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate);
								}
								if (_hoops_PCHA)
									glColor3fv(&_hoops_PCHA[_hoops_HCGS].red);
								if (matrix) {
									_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HSHSA);
									if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], _hoops_HSHSA, _hoops_SRHHC);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SRHHC, _hoops_HSHSA, _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&_hoops_HSHSA.x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv(&points[_hoops_HCGS].x);
								}

								_hoops_HCGS = _hoops_AIHA[j-2];
								if (_hoops_CSRGR->_hoops_SPGRC) {
									(*_hoops_CSRGR->glMultiTexCoord2fvARB)(GL_TEXTURE0_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
									(*_hoops_CSRGR->glMultiTexCoord3fvARB)(GL_TEXTURE1_ARB, &_hoops_CCHA[_hoops_HCGS*_hoops_GSHA+2]);
								}
								else if (_hoops_CCHA) {
									glTexCoord2fv (&_hoops_CCHA[_hoops_HCGS*_hoops_GSHA]);
								}
								else if (ts->_hoops_HCHA) {
									glTexCoord1f (ts->_hoops_HCHA[_hoops_HCGS] * _hoops_RRA->_hoops_CICP.scale + _hoops_RRA->_hoops_CICP.translate);
								}
								if (_hoops_PCHA)
									glColor3fv(&_hoops_PCHA[_hoops_HCGS].red);
								if (matrix) {
									_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HSHSA);
									if (_hoops_ICHA) {
										_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], _hoops_HSHSA, _hoops_SRHHC);
										_hoops_RRCRC (_hoops_RRIRC, _hoops_SRHHC, _hoops_HSHSA, _hoops_CSRGR->_hoops_SRIRC);
									}
									glVertex3fv (&_hoops_HSHSA.x);
								}
								else {
									if (_hoops_ICHA)
										_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
									glVertex3fv(&points[_hoops_HCGS].x);
								}
								_hoops_IRHHC++;
							}
							else
								_hoops_IRHHC = 0;
							j++;
						}
					}
					j = _hoops_SAHAR;
					_hoops_SSPAR = _hoops_PGGHC;
				}
				glEnd();
			}
		}
	} break;
#endif

