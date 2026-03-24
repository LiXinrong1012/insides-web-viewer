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
 * $Id: obf_tmp.txt 1.165 2010-10-20 18:15:31 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"

#ifndef DISABLE_UNSET

struct _hoops_ARPRGR {
	Type					type;
	Option_Value const *	option;
#		define	_hoops_PAGIC			0
#		define	_hoops_PRPRGR		1
#		define	_hoops_HRPRGR			2
#		define	_hoops_IRPRGR			3
	int						_hoops_AGRI;
	void *					_hoops_CRPRGR;
};

#define _hoops_SRPRGR		_hoops_RHAGP
#define _hoops_GAPRGR	_hoops_RHAGP+1
#define _hoops_RAPRGR		_hoops_RHAGP+2


 void _hoops_AAPRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {
	_hoops_ARPRGR *	pt = (_hoops_ARPRGR *)info;
	Type					type = pt->type;
	Option_Value const *	option = pt->option;
	Attribute *				thing;
	Attribute *				old = null;

	if (_hoops_SRCP->type == _hoops_IRCP) {	/* _hoops_CPSA _hoops_HRGR _hoops_IRS _hoops_CAGH */
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
			HI_Not_When_Streamed (_hoops_SRCP, "'UnSet' things");
			return;
		}

		if (_hoops_SRCP->owner->type == _hoops_PRAIR && type != HK_USER_OPTIONS) {
			_hoops_PHPGR (HEC_ATTRIBUTE, HES_DEFAULT_WORLD_ATTRIBUTE,
					"Not good to 'UnSet' the attribute settings in '/' -",
						 "They are the defaults for the world");
			return;
		}

		thing = _hoops_SRCP->_hoops_IPPGR;
	}
	else {
		Geometry *			geometry = (Geometry *)_hoops_SRCP;

		_hoops_SRCP = geometry->owner;
		thing = geometry->_hoops_IPPGR;
	}

	if (thing != null) do if (thing->type >= type) {
		if (thing->type > type)
			break;
		else {
			bool		_hoops_PAPRGR = false;

			thing->_hoops_CPGPR |= _hoops_CAHRA;

			switch (type) {
				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected 'UnSet_One'");
					goto _hoops_PP;
				}		/* _hoops_IHSA; */

				case HK_COLOR: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_SSGI *					color = (_hoops_SSGI *)thing;
					do {
						long				id = option->type->id;
						_hoops_ACSGA **		_hoops_ASRGR;
						_hoops_ACSGA *		_hoops_HAPCR;

						_hoops_ASRGR = &color->colors;

						while ((_hoops_HAPCR = *_hoops_ASRGR) != null) {
							bool				_hoops_HIHHH = false;

							if (!ANYBIT (_hoops_HAPCR->_hoops_GHA, id)) {}
							else if (_hoops_HAPCR->type != _hoops_GIGRA || option->value.option_list == null) {
								if ((_hoops_HAPCR->_hoops_GHA &= (int)~id) == 0)
									_hoops_HIHHH = true;
							}
							else {
								Option_Value const *			_hoops_AHSAA = option->value.option_list;

								do {
									_hoops_HCSGA alter *		_hoops_ICSGA = (_hoops_HCSGA alter *)_hoops_HAPCR;
									long						_hoops_HAPRGR = _hoops_AHSAA->type->id;

									if (ANYBIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_HAPRGR)) {
										_hoops_RGAIR (_hoops_ICSGA->name);
										int index = -1;

										if (_hoops_AHSAA->_hoops_AIPCR) {
											index = _hoops_AHSAA->value._hoops_RIARA[0];
											_hoops_HIR ** _hoops_ASRGR = &_hoops_ICSGA->_hoops_ISHIR._hoops_SCA;
											while (*_hoops_ASRGR) {
												if ((*_hoops_ASRGR)->_hoops_HGA == index) {
													_hoops_HIR * victim = *_hoops_ASRGR;
													*_hoops_ASRGR = victim->next;
													_hoops_RGAIR (victim->name);
													_hoops_HPRH (victim->texture);
													FREE (victim, _hoops_HIR);
													if (!_hoops_ICSGA->_hoops_ISHIR._hoops_SCA)
														index = -1;
													break;
												}
											}
										}
										else if (BIT(_hoops_HAPRGR, _hoops_RHGRA)) {
											HI_Free_Diffuse_Channel_List (_hoops_ICSGA->_hoops_ISHIR._hoops_SCA);
											_hoops_ICSGA->_hoops_ISHIR._hoops_SCA = null;
										}

										if (index == -1) {
											_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA &= (int)~_hoops_HAPRGR;
											if (BIT(_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, _hoops_RHGRA) &&
												_hoops_ICSGA->_hoops_ISHIR._hoops_SCA) {}
											else {
												int i=0;
												for (i=0; i<_hoops_GAGRA; i++) {
													if (BIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i]) &&
														_hoops_ICSGA->_hoops_ISHIR.texture[i] != null)
														break;
												}
												if (i == _hoops_GAGRA)
													_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA &= ~_hoops_CHGRA;
											}
										}

										if (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA == 0) {
											if ((_hoops_HAPCR->_hoops_GHA &= (int)~id) == 0)
												_hoops_HIHHH = true;
											break;
										}
									}
								} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
							}

							if (_hoops_HIHHH) {
								if ((color->_hoops_GHA &= (int)~id) == 0)
									_hoops_PAPRGR = true;

								*_hoops_ASRGR = _hoops_HAPCR->next;

								switch (_hoops_HAPCR->type) {
									case _hoops_SHGRA: {
										_hoops_PCSGA		*find = (_hoops_PCSGA*)_hoops_HAPCR;

										FREE (find, _hoops_PCSGA);
									}	break;

									case _hoops_PPCA: {
										_hoops_APCA		*_hoops_IRPA = (_hoops_APCA *)_hoops_HAPCR;

										_hoops_RGAIR (_hoops_IRPA->name);
										FREE (_hoops_IRPA, _hoops_APCA);
									}	break;

									case _hoops_GIGRA: {
										_hoops_HCSGA	*_hoops_RIGRA = (_hoops_HCSGA *)_hoops_HAPCR;

										HI_Free_Material_Names (&_hoops_RIGRA->_hoops_ISHIR, 1);
										_hoops_RGAIR (_hoops_RIGRA->name);
										FREE (_hoops_RIGRA, _hoops_HCSGA);
									}	break;
								}
							}
							else
								_hoops_ASRGR = &_hoops_HAPCR->next;
						}
					} while ((option = option->next) != null);
				}	break;

				case HK_DRIVER_OPTIONS: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_GAPIR *		_hoops_RAPIR = (_hoops_GAPIR *)thing;

					do {
						long				id = option->type->id;

						if (BIT (id, _hoops_HAPRP)) {
							id &= ~_hoops_HAPRP;
							if (!BIT (_hoops_RAPIR->_hoops_HAICA, id)) goto _hoops_PP;
							_hoops_RAPIR->_hoops_HAICA &= ~id;
							_hoops_RAPIR->_hoops_IAPRP &= ~id;
						}
						else {
							if (!BIT (_hoops_RAPIR->_hoops_IAICA, id)) goto _hoops_PP;
							_hoops_RAPIR->_hoops_IAICA &= ~id;
							_hoops_RAPIR->_hoops_HCARP &= ~id;
							if (id == _hoops_CRPRP) {
								HI_Free_Font_Names(_hoops_RAPIR->_hoops_SAPIR);
								_hoops_RAPIR->_hoops_SAPIR = null;
							}
							else if (id == _hoops_AAPRP) {
								HI_Free_Font_Names(_hoops_RAPIR->_hoops_GPPIR);
								_hoops_RAPIR->_hoops_GPPIR = null;
							}
						}
					} while ((option = option->next) != null);

					if (_hoops_RAPIR->_hoops_HAICA == 0 && _hoops_RAPIR->_hoops_IAICA == 0)
						_hoops_PAPRGR = true;
				}	break;

				case HK_USER_OPTIONS: {
					_hoops_HPPIR * _hoops_IPPIR = (_hoops_HPPIR *)thing;

					if (_hoops_IPPIR->_hoops_IGGSA)
						HI_Distill_User_Options(_hoops_RIGC, _hoops_IPPIR, _hoops_ACIAP|_hoops_PCIAP);

					switch (((_hoops_ARPRGR *)info)->_hoops_AGRI) {
						case _hoops_PAGIC: {
							do {
								long				id = option->type->id;
								Option_Value **_hoops_IAPRGR;
								Option_Value **_hoops_ASRGR,
																*_hoops_CSCIR;

								_hoops_ASRGR = &_hoops_IPPIR->option_list;

								_hoops_IAPRGR = _hoops_ASRGR;

								while ((_hoops_CSCIR = *_hoops_ASRGR) != null) {
									if (_hoops_CSCIR->type->id == id) {
										*_hoops_ASRGR = _hoops_CSCIR->next;
										_hoops_CSCIR->next = null;
										HI_Free_Option_List (_hoops_RIGC, _hoops_CSCIR);
										break;
									}
									_hoops_ASRGR = &_hoops_CSCIR->next;
								}
							} while ((option = option->next) != null);
						}	break;

						case _hoops_HRPRGR: {
							do {
								long				id = option->type->id;
								Option_Value **_hoops_IAPRGR;
								Option_Value **_hoops_ASRGR,
																*_hoops_CSCIR;

								_hoops_ASRGR = &_hoops_IPPIR->_hoops_APICA;

								_hoops_IAPRGR = _hoops_ASRGR;

								while ((_hoops_CSCIR = *_hoops_ASRGR) != null) {
									if (_hoops_CSCIR->type->id == id) {
										*_hoops_ASRGR = _hoops_CSCIR->next;
										_hoops_CSCIR->next = null;
										HI_Free_Option_List (_hoops_RIGC, _hoops_CSCIR);
										break;
									}
									_hoops_ASRGR = &_hoops_CSCIR->next;
								}
							} while ((option = option->next) != null);
						}	break;

						case _hoops_PRPRGR: {
							long					id = (long)(POINTER_SIZED_INT)pt->_hoops_CRPRGR;

							if (_hoops_IPPIR->_hoops_AGGSA) {
								_hoops_IPPIR->_hoops_AGGSA->RemoveItem(id);
								if (_hoops_IPPIR->_hoops_AGGSA->Count() == 0) {
									delete _hoops_IPPIR->_hoops_AGGSA;
									_hoops_IPPIR->_hoops_AGGSA = null;
								}
							}
						}	break;

						case _hoops_IRPRGR: {
							long					id = (long)(POINTER_SIZED_INT)pt->_hoops_CRPRGR;

							if (_hoops_IPPIR->_hoops_HGGSA) {
								_hoops_IHSCA * _hoops_CHSCA = null;
								_hoops_IPPIR->_hoops_HGGSA->RemoveItem(id, &_hoops_CHSCA);
								if (_hoops_CHSCA)
									delete _hoops_CHSCA;

								if (_hoops_IPPIR->_hoops_HGGSA->Count() == 0) {
									delete _hoops_IPPIR->_hoops_HGGSA;
									_hoops_IPPIR->_hoops_HGGSA = null;
								}
							}
						}	break;
					}

					if (_hoops_IPPIR->_hoops_AGGSA == null &&
						_hoops_IPPIR->_hoops_HGGSA == null &&
						_hoops_IPPIR->option_list == null &&
						_hoops_IPPIR->_hoops_APICA == null)
						_hoops_PAPRGR = true;
				}	break;

				case _hoops_CPPIR: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_SPPIR *		_hoops_GHPIR = (_hoops_SPPIR *)thing;

					if (option->type->_hoops_RCIIR == _hoops_ACIIR) {
						do {	// _hoops_CAPRGR
							long		id = option->type->id;
							int			index = id / 32;
							int			offset = id % 32;

							if (index < _hoops_GHPIR->count) {
								unsigned int		bit = 1UL << offset;

								if (BIT (_hoops_GHPIR->_hoops_SGCAA[index], bit)) {
									_hoops_GHPIR->_hoops_SGCAA[index] &= ~bit;
									_hoops_GHPIR->values[index] &= ~bit;

									_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[id]);
								}
							}
						} while ((option = option->next) != null);

						// _hoops_HPCAR _hoops_RHPA _hoops_RPP _hoops_PSP _hoops_PGSI, _hoops_HCCPR _hoops_SR _hoops_SSS _hoops_HHRPA _hoops_PISH _hoops_SIH
						_hoops_PAPRGR = (_hoops_GHPIR->_hoops_ACPGR == null);
						for (int i = 0; i < _hoops_GHPIR->count && _hoops_PAPRGR; i++) {
							if (_hoops_GHPIR->_hoops_SGCAA[i] != 0)
								_hoops_PAPRGR = false;
						}
					}
					else {		// _hoops_SAPRGR
						if (_hoops_GHPIR->_hoops_ACPGR != null) do {
							_hoops_PCACA **		_hoops_ASRGR = &_hoops_GHPIR->_hoops_ACPGR;
							_hoops_PCACA *		action;

							while ((action = *_hoops_ASRGR) != null) {
								if (action->type == option->type->id) {
									*_hoops_ASRGR = action->next;
									HI_Free_Conditional (&action->condition);
									FREE (action, _hoops_PCACA);
									break;
								}
								_hoops_ASRGR = &action->next;
							}
						} while ((option = option->next) != null && _hoops_GHPIR->_hoops_ACPGR != null);
						_hoops_PAPRGR = (_hoops_GHPIR->_hoops_ACPGR == null && _hoops_GHPIR->count == 0);
					}
				}	break;

				case HK_CALLBACK: {
#ifndef DISABLE_CALLBACKS
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_GCHIR *		callback = (_hoops_GCHIR *)thing;

					do {
						long				id = option->type->id;
						_hoops_IHACR		*_hoops_RCACR,
											**_hoops_ASRGR;

						_hoops_ASRGR = &callback->_hoops_ACHIR;
						_hoops_RGGA ((_hoops_RCACR = *_hoops_ASRGR) == null) {
							if (_hoops_RCACR->type == id) {
								*_hoops_ASRGR = _hoops_RCACR->next;
								_hoops_RCACR->next = null;
								_hoops_HPRH (_hoops_RCACR->name);
								FREE (_hoops_RCACR, _hoops_IHACR);
								break;
							}
							_hoops_ASRGR = &_hoops_RCACR->next;
						}
					} while ((option = option->next) != null);

					if (callback->_hoops_ACHIR == null)
						_hoops_PAPRGR = true;
#endif
				}	break;

				case HK_RENDERING_OPTIONS: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_RHAIR *		_hoops_AHAIR = (_hoops_RHAIR *)thing;

					do {
						long					id = option->type->id;

						if ((id & _hoops_AHGI) == _hoops_PSGAP) {
							id &= ~_hoops_AHGI;

							if (BIT (_hoops_AHAIR->_hoops_ISHCA, id)) {
								_hoops_AHAIR->_hoops_ISHCA  &= (int)~id;
								_hoops_AHAIR->_hoops_GHRAP &= (int)~id;
							}
						}
						else if ((id & _hoops_AHGI) == _hoops_ASGAP) {
							if (id == _hoops_HAI) {
								// _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_RPIP _hoops_IRS _hoops_HPHR _hoops_PIRA, _hoops_HIH _hoops_ARH _hoops_IRS _hoops_GPPRGR _hoops_PIAP.
								// _hoops_RPP _hoops_SGS _hoops_PIAP _hoops_HGGC _hoops_PHPP _hoops_RH _hoops_PSHR _hoops_PHRI, _hoops_SR _hoops_PAH _hoops_IPPRA *_hoops_SCH* _hoops_HAH
								if (BIT (_hoops_AHAIR->_hoops_SCIAA & _hoops_AHAIR->_hoops_RSIAA, _hoops_PGRAP)) {
									if (_hoops_AHAIR->_hoops_SHAAP == _hoops_CHRH &&
										_hoops_AHAIR->_hoops_GIAAP == 0) {
										// _hoops_APSH _hoops_PII _hoops_SCH _hoops_CSAP _hoops_IRS "_hoops_PSP _hoops_HHSA _hoops_HIAH", _hoops_HIS _hoops_HHSP _hoops_SAHR _hoops_SGS
										_hoops_AHAIR->_hoops_SHAAP = 0;
									}
									if (_hoops_AHAIR->_hoops_SHAAP == (_hoops_CHRH|_hoops_HIGRP|_hoops_AIGRP|_hoops_PIGRP) &&
										_hoops_AHAIR->_hoops_GIAAP == (_hoops_CHRH|_hoops_HIGRP|_hoops_AIGRP|_hoops_PIGRP) &&
										_hoops_AHAIR->_hoops_IHRH._hoops_ACGRP == _hoops_CIGRP &&
										_hoops_AHAIR->_hoops_IHRH.scale == 1.0f &&
										_hoops_AHAIR->_hoops_IHRH.translate == 0.0f &&
										_hoops_AHAIR->_hoops_IHRH.color == _hoops_GPSR::_hoops_IAHHP) {
										// _hoops_APSH _hoops_PII _hoops_SCH _hoops_CSAP _hoops_IRS "_hoops_HHSA _hoops_HIAH", _hoops_HIS _hoops_HHSP _hoops_HCR _hoops_IIGR _hoops_SCH
										_hoops_AHAIR->_hoops_SHAAP = 0;
										_hoops_AHAIR->_hoops_GIAAP = 0;
									}
								}
							}

							// _hoops_GPP _hoops_CCA _hoops_RH _hoops_GSSR _hoops_CIPH...
							id &= ~_hoops_AHGI;

							if (BIT (_hoops_AHAIR->_hoops_PSHCA, id)) {
								_hoops_AHAIR->_hoops_PSHCA  &= (int)~id;
								_hoops_AHAIR->_hoops_RRRAP &= (int)~id;
							}
						}
						else if (id == _hoops_GRRAP) {
							_hoops_AHAIR->_hoops_PRSI->mask &= ~_hoops_HRSI;
							_hoops_AHAIR->_hoops_PRSI->value &= ~_hoops_HRSI;

							if (_hoops_AHAIR->_hoops_PRSI->mask == 0) {
								_hoops_AHAIR->_hoops_SCIAA	 &= (int)~_hoops_SGICA;
								_hoops_AHAIR->_hoops_RSIAA &= (int)~_hoops_SGICA;
							}
						}
						else if (BIT (_hoops_AHAIR->_hoops_SCIAA, id)) {
							bool				_hoops_RPPRGR = false;

							if (option->value.option_list == null)
								_hoops_RPPRGR = true;
							else {
								Option_Value const * _hoops_AHSAA = option->value.option_list;

								do {
									long					_hoops_HAPRGR = _hoops_AHSAA->type->id;

									if (id == _hoops_GSIAA) {
										if (_hoops_HAPRGR == (long)_hoops_GGCAA(HK_COLOR)) {
											bool				_hoops_APPRGR = false;

											if (_hoops_AHSAA->value.option_list == null) {
												_hoops_AHAIR->locks->normal.mask.color = 0;
												_hoops_AHAIR->locks->normal.value.color = 0;
												ZERO_ARRAY (_hoops_AHAIR->locks->normal.mask._hoops_HAA, _hoops_IIGRA, int);
												ZERO_ARRAY (_hoops_AHAIR->locks->normal.value._hoops_HAA, _hoops_IIGRA, int);
												_hoops_APPRGR = true;
											}
											else {
												Option_Value const * _hoops_PPPRGR = _hoops_AHSAA->value.option_list;

												do {
													long					_hoops_HPPRGR = _hoops_PPPRGR->type->id;

													if (_hoops_PPPRGR->value.option_list == null) {
														int				i;

														_hoops_AHAIR->locks->normal.mask.color &= ~_hoops_HPPRGR;
														_hoops_AHAIR->locks->normal.value.color &= ~_hoops_HPPRGR;
														for (i=0; i<_hoops_IIGRA; i++) {
															int				_hoops_IPPRGR = 1 << i;

															if (BIT (_hoops_HPPRGR, _hoops_IPPRGR)) {
																_hoops_AHAIR->locks->normal.mask._hoops_HAA[i] = 0;
																_hoops_AHAIR->locks->normal.value._hoops_HAA[i] = 0;
															}
														}
													}
													else {
														Option_Value const * _hoops_CPPRGR = _hoops_PPPRGR->value.option_list;

														do {
															long			_hoops_SPPRGR = _hoops_CPPRGR->type->id;
															int				i;

															for (i=0; i<_hoops_IIGRA; i++) {
																int				_hoops_IPPRGR = 1 << i;

																if (BIT (_hoops_HPPRGR, _hoops_IPPRGR)) {
																	_hoops_AHAIR->locks->normal.mask._hoops_HAA[i] &= ~_hoops_SPPRGR;
																	_hoops_AHAIR->locks->normal.value._hoops_HAA[i] &= ~_hoops_SPPRGR;
																	if (_hoops_AHAIR->locks->normal.mask._hoops_HAA[i] == 0) {
																		_hoops_AHAIR->locks->normal.mask.color &= ~_hoops_IPPRGR;
																		_hoops_AHAIR->locks->normal.value.color &= ~_hoops_IPPRGR;
																	}
																}
															}
														} while ((_hoops_CPPRGR = _hoops_CPPRGR->next) != null);
													}
												} while ((_hoops_PPPRGR = _hoops_PPPRGR->next) != null);

												if (_hoops_AHAIR->locks->normal.mask.color == 0)
													_hoops_APPRGR = true;
											}

											if (_hoops_APPRGR) {
												_hoops_AHAIR->locks->normal.mask._hoops_IPPGR &= ~_hoops_GGCAA(HK_COLOR);
												_hoops_AHAIR->locks->normal.value._hoops_IPPGR &= ~_hoops_GGCAA(HK_COLOR);
											}
										}
										else if (_hoops_HAPRGR == (long)_hoops_GGCAA(HK_VISIBILITY)) {
											bool				_hoops_GHPRGR = false;

											if (_hoops_AHSAA->value.option_list == null) {
												_hoops_AHAIR->locks->normal.mask._hoops_RGP = 0;
												_hoops_AHAIR->locks->normal.value._hoops_RGP = 0;
												_hoops_GHPRGR = true;
											}
											else {
												Option_Value const * _hoops_RHPRGR = _hoops_AHSAA->value.option_list;

												do {
													long					_hoops_AHPRGR = _hoops_RHPRGR->type->id;

													_hoops_AHAIR->locks->normal.mask._hoops_RGP &= ~_hoops_AHPRGR;
													_hoops_AHAIR->locks->normal.value._hoops_RGP &= ~_hoops_AHPRGR;
												} while ((_hoops_RHPRGR = _hoops_RHPRGR->next) != null);

												if (_hoops_AHAIR->locks->normal.mask._hoops_RGP == 0)
													_hoops_GHPRGR = true;
											}

											if (_hoops_GHPRGR) {
												_hoops_AHAIR->locks->normal.mask._hoops_IPPGR &= ~_hoops_GGCAA(HK_VISIBILITY);
												_hoops_AHAIR->locks->normal.value._hoops_IPPGR &= ~_hoops_GGCAA(HK_VISIBILITY);
											}
										}
										else {
											_hoops_AHAIR->locks->normal.mask._hoops_IPPGR &= ~_hoops_HAPRGR;
											_hoops_AHAIR->locks->normal.value._hoops_IPPGR &= ~_hoops_HAPRGR;
										}

										if (_hoops_AHAIR->locks->normal.mask._hoops_IPPGR == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_CSHCA) {
										_hoops_AHAIR->_hoops_SSHCA.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_SSHCA.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_SSHCA.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_GGICA) {
										_hoops_AHAIR->_hoops_RGICA.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_RGICA.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_RGICA.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_IGICA) {
										_hoops_AHAIR->_hoops_AIAIR->mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_AIAIR->value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_AIAIR->mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_SGICA) {
										_hoops_AHAIR->_hoops_PRSI->mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_PRSI->value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_PRSI->mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_PRICA) {
										_hoops_AHAIR->_hoops_IIAIR->mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_IIAIR->value &= ~_hoops_HAPRGR;
										if ((_hoops_AHAIR->_hoops_IIAIR->mask & _hoops_ACCRP) == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_AGRAP) {
										_hoops_AHAIR->_hoops_IIAIR->mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_IIAIR->value &= ~_hoops_HAPRGR;
										if ((_hoops_AHAIR->_hoops_IIAIR->mask & _hoops_PICRP) == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_HRICA) {
										_hoops_AHAIR->geometry->mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->geometry->value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->geometry->mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_IRICA) {
										_hoops_AHAIR->geometry->_hoops_APPI.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->geometry->_hoops_APPI.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->geometry->_hoops_APPI.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_IRICA) {
										_hoops_AHAIR->geometry->_hoops_APPI.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->geometry->_hoops_APPI.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->geometry->_hoops_APPI.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_CRICA) {
										_hoops_AHAIR->geometry->_hoops_PSRIR.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->geometry->_hoops_PSRIR.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->geometry->_hoops_PSRIR.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_SRICA) {
										_hoops_AHAIR->geometry->_hoops_GAICA.mask &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->geometry->_hoops_GAICA.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_ARICA) {
										_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_RRICA) {
										_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_AGICA) {
										_hoops_AHAIR->_hoops_HGICA &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_PGICA		 &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_PGICA == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_SSGAP) {
										_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask == 0)
											_hoops_RPPRGR = true;
									}
									else if (id == _hoops_GGRAP) {
										_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask &= ~_hoops_HAPRGR;
										_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.value &= ~_hoops_HAPRGR;
										if (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask == 0)
											_hoops_RPPRGR = true;
									}
								} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
							}

							if (_hoops_RPPRGR) {
								_hoops_AHAIR->_hoops_SCIAA	 &= (int)~id;
								_hoops_AHAIR->_hoops_RSIAA &= (int)~id;
							}
						}
					} while ((option = option->next) != null);

					if (_hoops_AHAIR->_hoops_SCIAA == 0 &&
						_hoops_AHAIR->_hoops_PSHCA == 0 &&
						_hoops_AHAIR->_hoops_ISHCA == 0)
						_hoops_PAPRGR = true;
				}	break;

				case HK_HEURISTICS: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_GHAIR *			_hoops_GIGC = (_hoops_GHAIR *)thing;
					bool					_hoops_CCCIR = false;

					do {
						long					id = option->type->id;

						if (ANYBIT (_hoops_GIGC->mask, id)) {
							Option_Value const * _hoops_AHSAA = option->value.option_list;

							if (_hoops_AHSAA == null) {
								_hoops_GIGC->mask &= ~id;
								_hoops_GIGC->value &= ~id;
								if (id == _hoops_RAIRP) {
									_hoops_GIGC->_hoops_APH.mask = 0;
									_hoops_GIGC->_hoops_APH.value = 0;
								}
								_hoops_CCCIR = true;
							}
							else {
								if (id == _hoops_RAIRP) do {
									long	_hoops_HAPRGR = _hoops_AHSAA->type->id;

									if (ANYBIT (_hoops_GIGC->_hoops_APH.mask, _hoops_HAPRGR)) {
										_hoops_GIGC->_hoops_APH.mask &= ~_hoops_HAPRGR;
										_hoops_GIGC->_hoops_APH.value &= ~_hoops_HAPRGR;
										_hoops_CCCIR = true;
									}
								} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
								else do {
									long	_hoops_HAPRGR = _hoops_AHSAA->type->id;

									if (ANYBIT (_hoops_GIGC->mask, _hoops_HAPRGR)) {
										_hoops_GIGC->mask &= ~_hoops_HAPRGR;
										_hoops_GIGC->value &= ~_hoops_HAPRGR;
										_hoops_CCCIR = true;
									}
								} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
							}
						}
					} while ((option = option->next) != null);

					if (_hoops_GIGC->_hoops_APH.mask == 0)
						_hoops_GIGC->mask &= ~_hoops_RAIRP;

					if (_hoops_GIGC->mask == 0)
						_hoops_PAPRGR = true;
					else if (!_hoops_CCCIR)
						goto _hoops_PP;
				}	break;


				case HK_SELECTABILITY: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_ASAIR *			_hoops_AAICA = (_hoops_ASAIR *)thing;

					do {
						long					id = option->type->id;

						_hoops_AAICA->up &= ~id;
						_hoops_AAICA->down &= ~id;
						_hoops_AAICA->_hoops_RHARP &= ~id;
						_hoops_AAICA->_hoops_AHARP &= ~id;
						_hoops_AAICA->_hoops_HHARP &= ~id;
						_hoops_AAICA->mask &= ~id;
					} while ((option = option->next) != null);

					if (_hoops_AAICA->mask == 0)
						_hoops_PAPRGR = true;
				}	break;

				case HK_TEXT_FONT: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_AGPIR *			font = (_hoops_AGPIR *)thing;

					do {
						_hoops_SAPAP		id = (_hoops_SAPAP)option->type->id;

						if (id == _hoops_GPPAP) {
							_hoops_IGPIR	*name;
							_hoops_IGPIR	*next;

							if ((name = font->_hoops_HGPIR) != null) do {
								next = name->next;
								if (name->_hoops_SSSGP == GFN_SPECIFIED)
									_hoops_RGAIR (name->specified);
								FREE (name, _hoops_IGPIR);
							} while ((name = next) != null);

							font->_hoops_HGPIR = null;
						}

						font->_hoops_HAICA &= ~id;
					} while ((option = option->next) != null);

					if (font->_hoops_HGPIR == null && font->_hoops_HAICA == 0)
						_hoops_PAPRGR = true;
				}	break;

#define _hoops_SASAA		_hoops_ASPCR	/* _hoops_GII _hoops_IGRH _hoops_HAR _hoops_IGI _hoops_IH _hoops_IRS _hoops_HPHR _hoops_HPRC, _hoops_SPASR _hoops_RGSR _hoops_GGR _hoops_PHPRGR */
				case HK_VISIBILITY: {
					old = HI_Clone_Attributes (_hoops_RIGC, thing, _hoops_SRCP, false, null);
					_hoops_RSAIR *			vis = (_hoops_RSAIR *)thing;
					bool					_hoops_CCCIR = false;

					do {
						long					id = option->type->id;
						Option_Value const * _hoops_AHSAA = option->value.option_list;

						if (id == T_CUT_GEOMETRY) {
							if (BIT (vis->mask, T_CUT_GEOMETRY)) {
								if (_hoops_AHSAA == null) {
									vis->mask &= ~id;
									vis->value &= ~id;
									_hoops_CCCIR = true;
								}
								else {
									do {
										long	_hoops_HAPRGR = _hoops_AHSAA->type->id;

										if (BIT (vis->_hoops_PRIGA.mask, _hoops_HAPRGR)) {
											vis->_hoops_PRIGA.mask &= ~_hoops_HAPRGR;
											vis->_hoops_PRIGA.value &= ~_hoops_HAPRGR;
											_hoops_CCCIR = true;
										}
									} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);

									if (vis->_hoops_PRIGA.mask == 0) {
										vis->mask &= ~id;
										vis->value &= ~id;
									}
								}
							}
						}
						else if (id == _hoops_SASAA) {
							if (BIT (vis->mask, T_CUT_GEOMETRY) &&
								BIT (vis->_hoops_PRIGA.mask, T_LINES)) {
								vis->_hoops_PRIGA.mask &= ~T_LINES;
								vis->_hoops_PRIGA.value &= ~T_LINES;
								if (vis->_hoops_PRIGA.mask == 0) {
									vis->mask &= ~T_CUT_GEOMETRY;
									vis->value &= ~T_CUT_GEOMETRY;
								}
								_hoops_CCCIR = true;
							}
						}
						else if (id == T_ANY_SHADOW) {
							if (BIT (vis->mask, T_ANY_SHADOW)) {
								if (_hoops_AHSAA == null) {
									vis->mask &= ~id;
									vis->value &= ~id;
									_hoops_CCCIR = true;
								}
								else {
									do {
										long	_hoops_HAPRGR = _hoops_AHSAA->type->id;

										if (BIT (vis->_hoops_SPSS.mask, _hoops_HAPRGR)) {
											vis->_hoops_SPSS.mask &= ~_hoops_HAPRGR;
											vis->_hoops_SPSS.value &= ~_hoops_HAPRGR;
											_hoops_CCCIR = true;
										}
									} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);

									if (vis->_hoops_SPSS.mask == 0) {
										vis->mask &= ~id;
										vis->value &= ~id;
									}
								}
							}
						}
						else if (ANYBIT (vis->mask, id)) {
							if (_hoops_AHSAA == null) {
								vis->mask &= ~id;
								vis->value &= ~id;
								_hoops_CCCIR = true;
							}
							else {
								do {
									long	_hoops_HAPRGR = _hoops_AHSAA->type->id;

									if (ANYBIT (vis->mask, _hoops_HAPRGR)) {
										vis->mask &= ~_hoops_HAPRGR;
										vis->value &= ~_hoops_HAPRGR;
										_hoops_CCCIR = true;
									}
								} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
							}
						}
					} while ((option = option->next) != null);


					if (vis->mask == 0)
						_hoops_PAPRGR = true;
					else if (!_hoops_CCCIR)
						goto _hoops_PP;
				}	break;
			}

			if (_hoops_PAPRGR) {
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, old, null);
				HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)thing);
			}
			else	/* _hoops_PHIH _hoops_PA _hoops_SGS _hoops_GHCA _hoops_HS _hoops_RPII _hoops_RHSI _hoops_ARRS _hoops_SGS _hoops_SR _hoops_HGGC _hoops_HS _hoops_AARI */
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, old, thing);

			break;
		}
	} while ((thing = thing->next) != null);

_hoops_PP:
	if (old != null)
		_hoops_HPRH (old);
}


local void _hoops_HHPRGR (
	_hoops_AIGPR *		_hoops_RIGC,
	long						id) {
	Polyhedron *				_hoops_IPRI;
	int							offset;

	_hoops_IPRI = _hoops_RIGC->open_list->info._hoops_IPRI._hoops_IGRPR;
	offset	   = _hoops_RIGC->open_list->info._hoops_IPRI.offset;

	if (_hoops_IPRI->type == _hoops_CSIP) {
		PolyCylinder *				_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
		_hoops_AGHIR *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;
		_hoops_CGHIR *			flags;

		if ((flags = _hoops_PGHIR->flags) == null ||
			!ANYBIT (flags[offset], _hoops_GPPRA|
									_hoops_RPPRA)) {
			HE_ERROR (HEC_VERTEX, HES_COLOR,"No color set on this vertex");
			return;
		}

		if (ANYBIT (id, Color_FACE)) {
			if (BIT (flags[offset], _hoops_GIRRA)) {
				if (--_hoops_PGHIR->_hoops_RCRHR == 0) {
					if (_hoops_PGHIR->fcolors != _hoops_PGHIR->ecolors)
						FREE_ARRAY (_hoops_PGHIR->fcolors, _hoops_HSPIR->point_count, RGB);
					_hoops_PGHIR->fcolors = null;
				}
				else
					_hoops_PGHIR->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;
			}
			else if (BIT (flags[offset], _hoops_CHRRA)) {
				if (--_hoops_PGHIR->_hoops_SIRHR == 0) {
					if (_hoops_PGHIR->_hoops_IGHIR != _hoops_PGHIR->_hoops_HGHIR)
						FREE_ARRAY (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
					_hoops_PGHIR->_hoops_IGHIR = null;
				}
				else
					_hoops_PGHIR->_hoops_IGHIR[offset] = 0.0f;
			}
			flags[offset] &= ~_hoops_RPPRA;
		}

		if (BIT (id, Color_EDGE)) {
			if (BIT (flags[offset], _hoops_SHRRA)) {
				if (--_hoops_PGHIR->_hoops_SCHPR == 0) {
					if (_hoops_PGHIR->ecolors != _hoops_PGHIR->fcolors)
						FREE_ARRAY (_hoops_PGHIR->ecolors, _hoops_HSPIR->point_count, RGB);
					_hoops_PGHIR->ecolors = null;
				}
				else
					_hoops_PGHIR->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;
			}
			else if (BIT (flags[offset], _hoops_IHRRA)) {
				if (--_hoops_PGHIR->_hoops_CCHPR == 0) {
					if (_hoops_PGHIR->_hoops_HGHIR != _hoops_PGHIR->_hoops_IGHIR)
						FREE_ARRAY (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
					_hoops_PGHIR->_hoops_HGHIR = null;
				}
				else
					_hoops_PGHIR->_hoops_HGHIR[offset] = 0.0f;
			}
			flags[offset] &= ~_hoops_GPPRA;
		}

		if (_hoops_PGHIR->_hoops_RCRHR == 0 &&
			_hoops_PGHIR->_hoops_SIRHR == 0 &&
			_hoops_PGHIR->_hoops_SCHPR == 0 &&
			_hoops_PGHIR->_hoops_CCHPR == 0) {
			/* _hoops_HCR _hoops_PPRGA! */
			FREE_ARRAY (_hoops_PGHIR->flags, _hoops_HSPIR->point_count, _hoops_CGHIR);
			FREE (_hoops_PGHIR, _hoops_AGHIR);
			_hoops_HSPIR->_hoops_RGHIR = null;
		}
	}
	else {
		Local_Vertex_Attributes		*_hoops_SPRI;
		Local_Vertex_Flags			*flags;
		int							_hoops_PIRRA;

		_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
		_hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;

		if ((flags = _hoops_SPRI->flags) == null ||
			!ANYBIT (flags[offset], _hoops_APPRA|
									_hoops_PPPRA|
									_hoops_HPPRA)) {
			HE_ERROR (HEC_VERTEX, HES_COLOR, "No color set on this vertex");
			return;
		}

		if (BIT (id, Color_VERTEX)) {
			if (BIT (flags[offset], _hoops_HCRRA)) {
				if (--_hoops_SPRI->_hoops_ICRRA == 0) {
					if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
						FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
					_hoops_SPRI->_hoops_PAHIR = null;
				}
				else
					_hoops_SPRI->_hoops_PAHIR[offset] = _hoops_GPSR::_hoops_RPSR;

				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
			}
			else if (BIT (flags[offset], _hoops_SIRRA)) {
				if (--_hoops_SPRI->_hoops_PCRRA == 0) {
					if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
						FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
					_hoops_SPRI->_hoops_HAHIR = null;
				}
				else
					_hoops_SPRI->_hoops_HAHIR[offset] = 0.0f;

				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
			}
			else if (BIT (flags[offset], _hoops_CCRRA)) {
				if (--_hoops_SPRI->_hoops_HIRRA == 0) {
					FREE_ARRAY (_hoops_SPRI->_hoops_IAHIR, _hoops_IPRI->point_count, RGBAS32);
					_hoops_SPRI->_hoops_IAHIR = null;
				}
				else
					_hoops_SPRI->_hoops_IAHIR[offset] = _hoops_CAHSR::_hoops_SAHSR;

				_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
			}
			flags[offset] &= ~_hoops_APPRA;
		}

		if (BIT (id, Color_EDGE)) {
			if (BIT (flags[offset], _hoops_PPHPR)) {
				if (--_hoops_SPRI->_hoops_SCHPR == 0) {
					if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
						FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
					_hoops_SPRI->ecolors = null;
				}
				else
					_hoops_SPRI->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;

				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
			}
			else if (BIT (flags[offset], _hoops_RPHPR)) {
				if (--_hoops_SPRI->_hoops_CCHPR == 0) {
					if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
						FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
					_hoops_SPRI->_hoops_HGHIR = null;
				}
				else
					_hoops_SPRI->_hoops_HGHIR[offset] = 0.0f;

				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
			}
			flags[offset] &= ~_hoops_PPPRA;
		}

		if (ANYBIT (id, Color_FACE)) {
			if (BIT (flags[offset], _hoops_AARHR)) {
				if (--_hoops_SPRI->_hoops_RCRHR == 0) {
					if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
						FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_IPRI->point_count +
													_hoops_IPRI->_hoops_GCRHR, RGB);
					_hoops_SPRI->fcolors = null;
				}
				else
					_hoops_SPRI->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;

				_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
			}
			else if (BIT (flags[offset], _hoops_HARHR)) {
				if (--_hoops_SPRI->_hoops_SIRHR == 0) {
					if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
						FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_IPRI->point_count +
													_hoops_IPRI->_hoops_GCRHR, _hoops_ACGHR);
					_hoops_SPRI->_hoops_IGHIR = null;
				}
				else
					_hoops_SPRI->_hoops_IGHIR[offset] = 0.0f;

				_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
			}
			flags[offset] &= ~_hoops_HPPRA;
		}

		if (_hoops_IPRI->owner != null) {
			if (_hoops_PIRRA != 0) {
				if (_hoops_SPRI->_hoops_HIRRA == 0)
					HI_Less_Transparencies (_hoops_RIGC, _hoops_IPRI->owner, 1);
			}
			else {
				if (_hoops_SPRI->_hoops_HIRRA != 0)
					HI_More_Transparencies (_hoops_RIGC, _hoops_IPRI->owner, 1);
			}
		}
	}

	_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
}

local void _hoops_IHPRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	Type					type,
	Option_Value *			option) {

	if (option == null)
		return;

	if (_hoops_RIGC->open_list == null) {
		if (!HI_Find_Our_Open (_hoops_RIGC))
			goto _hoops_PP;

		if (_hoops_RIGC->open_list != null) /* _hoops_IHGS _hoops_RHRIR... */
			_hoops_IHPRGR (_hoops_RIGC, type, option); /* _hoops_HA _hoops_HPPR _hoops_GICS */
	}
	else switch (_hoops_RIGC->open_list->_hoops_GCRIR) {
		case _hoops_RCRIR: {
			_hoops_ARPRGR			pt;

			if (BIT (_hoops_RIGC->open_list->_hoops_RRHH, _hoops_APAPP) &&
				BIT (_hoops_RIGC->open_list->info.segment._hoops_IGRPR->_hoops_PHSI, _hoops_PRSIR)) {
				HE_ERROR2 (HEC_INVALID_INPUT, HES_AUTO_STREAMING_MODE,
						"Can't 'UnSet' - you're in 'auto-streaming' mode -",
							 "(No segment was ever explicitly opened)");
				goto _hoops_PP;
			}

			pt.type = type;
			pt.option = option;
			pt._hoops_AGRI = _hoops_PAGIC;
			pt._hoops_CRPRGR = 0;
			if (type == _hoops_GAPRGR) {
				pt.type = HK_USER_OPTIONS;
				pt._hoops_AGRI = _hoops_HRPRGR;
			}
			else if (type == _hoops_SRPRGR) {
				pt.type = HK_USER_OPTIONS;
				pt._hoops_AGRI = _hoops_PRPRGR;
				pt._hoops_CRPRGR = (void*)option;
				pt.option = option = null;
			}
			else if (type == _hoops_RAPRGR) {
				pt.type = HK_USER_OPTIONS;
				pt._hoops_AGRI = _hoops_IRPRGR;
				pt._hoops_CRPRGR = (void*)option;
				pt.option = option = null;
			}

			_hoops_RPPPR();
			_hoops_AAPRGR (_hoops_RIGC, _hoops_RIGC->open_list->info.segment._hoops_IGRPR, (void *)&pt);
			_hoops_IRRPR();
		}	break;

		case _hoops_HCRIR: {
#  ifndef _hoops_GCGHR
			_hoops_ARPRGR			pt;

			pt.type = type;
			pt.option = option;
			pt._hoops_AGRI = _hoops_PAGIC;
			pt._hoops_CRPRGR = 0;
			if (type == _hoops_GAPRGR) {
				pt.type = HK_USER_OPTIONS;
				pt._hoops_AGRI = _hoops_HRPRGR;
			}
			else if (type == _hoops_SRPRGR) {
				pt.type = HK_USER_OPTIONS;
				pt._hoops_AGRI = _hoops_PRPRGR;
				pt._hoops_CRPRGR = (void*)option;
				pt.option = option = null;
			}
			else if (type == _hoops_RAPRGR) {
				pt.type = HK_USER_OPTIONS;
				pt._hoops_AGRI = _hoops_IRPRGR;
				pt._hoops_CRPRGR = (void*)option;
				pt.option = option = null;
			}

			_hoops_RPPPR();
			_hoops_AAPRGR (_hoops_RIGC, (_hoops_CRCP *)_hoops_RIGC->open_list->info.geometry._hoops_IGRPR,(void *)&pt);
			_hoops_IRRPR();
#  endif
		}	break;


#ifndef DISABLE_GEOMETRY_ATTRIBUTES
		case _hoops_CCRIR: {
#  ifndef _hoops_GCGHR
			if (type == HK_COLOR && option->next == null && option->type->id == Color_EDGE) {
				PUSHNAME(_hoops_RIGC);
				HC_UnSet_Color ();
				POPNAME(_hoops_RIGC);
				goto _hoops_PP;
			}
			else
#  endif
#  ifndef _hoops_IIICA
			if (type == HK_VISIBILITY && option->next == null && option->type->id == T_ANY_EDGE) {
				PUSHNAME(_hoops_RIGC);
				HC_UnSet_Visibility ();
				POPNAME(_hoops_RIGC);
				goto _hoops_PP;
			}
			else
#  endif

			HE_ERROR (HEC_EDGE, HES_CANNOT_UNSET_ATTRIBUTE,"Can't unset that on an open 'edge'");
		}	break;

		case _hoops_SCRIR: {
#  ifndef _hoops_GCGHR
			if (type == HK_COLOR) {
				_hoops_RPPPR();
				do _hoops_HHPRGR (_hoops_RIGC, option->type->id);
				while ((option = option->next) != null);
				_hoops_IRRPR();
				goto _hoops_PP;
			}
			else
#  endif

			HE_ERROR (HEC_VERTEX, HES_CANNOT_UNSET_ATTRIBUTE,"Can't unset that on an open 'vertex'");
		}	break;

		case _hoops_ICRIR: {
#  ifndef _hoops_GCGHR
			if (type == HK_COLOR && option->next == null && !ANYBIT (option->type->id, ~Color_FACE)) {
				PUSHNAME(_hoops_RIGC);
				HC_UnSet_Color ();
				POPNAME(_hoops_RIGC);
				goto _hoops_PP;
			}
			else
#  endif
#  ifndef _hoops_IIICA
			if (type == HK_VISIBILITY && option->next == null && !ANYBIT (option->type->id, ~T_FACES)) {
				PUSHNAME(_hoops_RIGC);
				HC_UnSet_Visibility ();
				POPNAME(_hoops_RIGC);
				goto _hoops_PP;
			}
			else
#  endif

			HE_ERROR (HEC_FACE, HES_CANNOT_UNSET_ATTRIBUTE, "Can't unset that on an open 'face'");
		}	break;

		case _hoops_GSRIR: {
#  ifndef _hoops_GCGHR
			if (type == HK_COLOR && option->next == null && !ANYBIT (option->type->id, ~Color_FACE)) {
				PUSHNAME(_hoops_RIGC);
				HC_UnSet_Color ();
				POPNAME(_hoops_RIGC);
				goto _hoops_PP;
			}
			else
#  endif
#  ifndef _hoops_IIICA
			if (type == HK_VISIBILITY && option->next == null && !ANYBIT (option->type->id, ~T_FACES)) {
				PUSHNAME(_hoops_RIGC);
				HC_UnSet_Visibility ();
				POPNAME(_hoops_RIGC);
				goto _hoops_PP;
			}
			else
#  endif

			HE_ERROR (HEC_FACE, HES_CANNOT_UNSET_ATTRIBUTE, "Can't unset that on an open 'region'");
		}	break;
#endif

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Unexpected open type");
		}	break;
	}

  _hoops_PP:;
	if (option != null)
		HI_Free_Option_List (_hoops_RIGC, option);
}

#endif



HC_INTERFACE void HC_CDECL HC_UnSet_One_Driver_Option (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Driver_Option");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Driver_Option (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_AAPPP),&option, _hoops_CGPCR))
		return;

	_hoops_IHPRGR (context, HK_DRIVER_OPTIONS, option);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_One_Heuristic (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Heuristic");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Heuristic (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_PAPPP),
						   &option, _hoops_CGPCR))
						   return;

	if (option == null)
		return;

	_hoops_IHPRGR (context, HK_HEURISTICS, option);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_One_Color (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Color");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Color (%S);\n", which));
	);

	Option_Value *	option;

	if ((option = HI_Decipher_Color_Type (context, which, _hoops_SIACR)) == null)
		return;

	_hoops_IHPRGR (context, HK_COLOR, option);
#endif
}




HC_INTERFACE void HC_CDECL HC_UnSet_One_Rendering_Option (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Rendering_Option");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Rendering_Option (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_HAPPP),
						   &option, _hoops_CGPCR))
						   return;

	if (option == null)
		return;

	_hoops_IHPRGR (context, HK_RENDERING_OPTIONS, option);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_One_Selectability (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Selectability");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Selectability (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_IAPPP),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, HK_SELECTABILITY, option);
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_One_Text_Font (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Text_Font");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Text_Font (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_CAPPP),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, HK_TEXT_FONT, option);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_One_User_Option (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_User_Option");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_User_Option (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_SAPPP),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, HK_USER_OPTIONS, option);
#endif
}




HC_INTERFACE void HC_CDECL HC_UnSet_One_Unicode_Option (
	Karacter const *	which)
{
	_hoops_PAPPR context("UnSet_One_Unicode_Option");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Unicode_Option (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_KOptions (context, which, _hoops_CIACR (_hoops_CPPPP), &option, _hoops_CGPCR))
		return;

	_hoops_IHPRGR (context, _hoops_GAPRGR, option);
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_One_User_Index (
	long				index)
{
	_hoops_PAPPR context("UnSet_One_User_Index");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_UnSet_One_User_Index (\"%D\");\n", index));
	);

	_hoops_IHPRGR (context, _hoops_SRPRGR, (Option_Value *)(POINTER_SIZED_INT)index);
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_One_Condition (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Condition");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Condition (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_GGPCA),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, _hoops_CPPIR, option);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_One_Conditional_Action (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Conditional_Action");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Conditional_Action (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_SRPCA),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, _hoops_CPPIR, option);
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_One_Callback (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Callback (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_IIACR),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, HK_CALLBACK, option);
#endif
#endif
}




HC_INTERFACE void HC_CDECL HC_UnSet_One_Visibility (
	char const *		which)
{
	_hoops_PAPPR context("UnSet_One_Visibility");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnSet_One_Visibility (%S);\n", which));
	);

	Option_Value *	option;

	if (!HI_Parse_Options (context, which, _hoops_CIACR (_hoops_CPSAA),
						   &option, _hoops_CGPCR))
						   return;

	_hoops_IHPRGR (context, HK_VISIBILITY, option);
#endif
}




HC_INTERFACE void HC_CDECL HC_UnSet_One_User_Data (
	POINTER_SIZED_INT	index)
{
	_hoops_PAPPR context("UnSet_One_User_Data");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_UnSet_One_User_Data (\"%D\");\n", index));
	);

	_hoops_IHPRGR (context, _hoops_RAPRGR, (Option_Value *)(POINTER_SIZED_INT)index);
#endif
}











