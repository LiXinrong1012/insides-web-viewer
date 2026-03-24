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
 * $Id: hpserror.h,v 1.148 2010-08-11 21:16:37 conor Exp $
 */

#ifndef HOOPS_ERRORS_DEFINED

/*
 * These definitions are subject to change from HOOPS release to
 * release. Please references these items by their HEC_ and HES_
 * defines rather than by specific number.
 */

// Do NOT use *_UNDEFINED for normal errors, find or make an appropriate one
#define HEC_UNDEFINED					0
#define			HES_UNDEFINED							0




#define HEC_DEBUG						1
#define			HES_DEBUG								1

/*
 * Internal HOOPS Errors
 */
#define HEC_INTERNAL_ERROR				2
#define			HES_PROCEDURAL_ERROR					2
#define			HES_DATA_ERROR							3
#define			HES_RECURSIVE_UPDATE					4

/*
 * Memory Errors
 */
#define HEC_MEMORY						3
#define			HES_OUT_OF_MEMORY						4
#define			HES_BUFFER_OVERFLOW						5
#define			HES_ALLOCATE_MEMORY_FAILED				6
#define			HES_MEMORY_USAGE						7
#define			HES_SYSTEM_REJECTED_FREED_MEMORY		8
#define			HES_MEMORY_PROFILE_NOT_COMPILED			9


/*
 * Attribute Errors
 */
#define HEC_CALLBACK					4
#define HEC_CAMERA						5
#define HEC_COLOR						6
#define HEC_COLOR_MAP					7
#define HEC_DRIVER						8
#define HEC_HANDEDNESS					9
#define HEC_HEURISTIC					10
#define HEC_HOOPS_SYSTEM				11
#define HEC_METAFILE					12
#define HEC_MODELLING_MATRIX			13
#define HEC_RENDERING					15
#define HEC_TEXT						16
#define HEC_WINDOW						17
#define HEC_PARAMETER					18
#define HEC_PATTERN						19
#define HEC_TEXTURE						20


/*
 * Geometry Errors
 */
#define HEC_CIRCLE						21
#define HEC_CIRCULAR_ARC				22
#define HEC_CUTTING_PLANE				23
#define HEC_DISTANT_LIGHT				24
#define HEC_EDGE						25
#define HEC_ELLIPSE						26
#define HEC_ELLIPTICAL_ARC				27
#define HEC_FACE						28
#define HEC_GEOMETRY					29
#define HEC_IMAGE						30
#define HEC_LOCAL_LIGHT					31
#define HEC_NORMAL						32
#define HEC_POLYGON						33
#define HEC_POLYLINE					34
#define HEC_TRISTRIP					35
#define HEC_VERTEX						36
#define HEC_INK							37
#define HEC_MARKER						38
#define HEC_RENUMBER_KEY				39
#define HEC_SPOT_LIGHT					40
/* note: break in sequence to allow system and driver errors  (defined below) to not change */
#define HEC_MSET_FACE					110
#define HEC_LOD_MODULE					111	 /* must match mxmain.h */
#define HEC_LOD							112	 /* lod-related, but not from a mx*.c file */
#define HEC_CURVE						113
#define HEC_SURFACE						114
#define HEC_CYLINDER					115
#define HEC_REGION						116
#define HEC_SPHERE						117
#define HEC_GLYPH						118
#define HEC_LINE_STYLE					119


/*
 * System Errors
 */
#define HEC_COMPUTE						41
#define HEC_FILE_IO						42
#define HEC_INVALID_INPUT				43
#define HEC_EVENT_HANDLER				44
#define HEC_ERROR_HANDLER				45
#define HEC_EXIT_HANDLER				46
#define HEC_INVALID_KEY					47
#define HEC_SEGMENT						48
#define HEC_SELECTION					49
#define HEC_SYNTAX						50
#define HEC_MISC						51

#define HEC_ATTRIBUTE					52
#define HEC_PRIORITY					53
#define HEC_BOUNDING_BOX				54
#define HEC_VISIBILITY					55
#define HEC_MSET_VERTEX					56
#define HEC_FATAL_ERROR					57
#define HEC_GEOMETRY_OR_SEGMENT			58
#define HEC_OPTION_TYPE					59
#define HEC_SYSTEM						60
#define HEC_ALIAS						61
#define HEC_STYLE						62
#define HEC_OWNER						63
#define HEC_INCLUDE						64
#define HEC_EXISTENCE					65
#define HEC_BRING_TO_FRONT				66
#define HEC_CONTENT						67
#define HEC_LOCATION					68
#define HEC_BUTTON						69
#define HEC_STRING_EVENT				70
#define HEC_CIRCULAR_WEDGE				71
#define HEC_CIRCULAR_CHORD				72
#define HEC_INFO						73
#define HEC_AREA_LIGHT					74
#define HEC_STRING_CURSOR				75
#define HEC_GRID						76
#define HEC_NOT_AVAILABLE_FROM_FORTRAN	77
#define HEC_START_DRIVERS				78
#define HEC_REFERENCE					120


/*
 * Driver Errors
 */
#define HEC_CGM_DRIVER					79
#define HEC_GL_DRIVER					80
#define HEC_HPGL_DRIVER					81
#define HEC_IMAGE_DRIVER				82
#define HEC_MAC_DRIVER					83
#define HEC_METAWINDOW_DRIVER			84
#define HEC_MSW_DRIVER					85
#define HEC_OPENGL_DRIVER				86
#define HEC_PEX_DRIVER					87
#define HEC_PICT_DRIVER					88
#define HEC_POSTSCRIPT_DRIVER			89
#define HEC_PRINTF_DRIVER				90
#define HEC_SBX_DRIVER					91
#define HEC_THIRDPARTY_DRIVER			92
#define HEC_ARTIST_DRIVER				92
#define HEC_MATROX_DRIVER				92
#define HEC_UIS_DRIVER					93
#define HEC_X11_DRIVER					94
#define HEC_XGL_DRIVER					95
#define HEC_HPGL2_DRIVER				96
#define HEC_DIRECT3D_DRIVER				97
#define HEC_QUARTZ_DRIVER				98
#define HEC_CHARACTER_ATTRIBUTE			99
#define	HEC_MUNSET						100
#define HEC_WHIP2D_DRIVER				101
#define HEC_PDF_DRIVER                  102
#define HEC_DX9_DRIVER					103
#define HEC_EXTERNAL					104
/*codes 110 - 130 are reserved for future system errors */

#define HEC_CONDITIONS					140
#define HEC_USER_OPTIONS				141
#define HEC_JPEG						142
#define HEC_MSHOW						143
#define HEC_TEXTURE_MATRIX				144


/*
 * Specific Errors
 */
#define			HES_ABORT_FUNCTION						10
#define			HES_ABORT_REQUESTED_BY_APPLICATION		11
#define			HES_ACQUIRE_GLX_CONFIG_FAILED			12
#define			HES_AIR									13
#define			HES_AIR_NOT_PRESENT						14
#define			HES_ALLOC_COLOR_OVERLAY_PLANE			15
#define			HES_ALLOC_OVERLAY_PLANE					16
#define			HES_ALREADY_DEFINED						17
#define			HES_ALREADY_INCLUDED					18
#define			HES_ALREADY_STYLED						19
#define			HES_ASCII_WRITE_TO_FILE_FAILED			20
#define			HES_AT_SIGN_MISSING_FROM_KEY			21
#define			HES_AUTO_STREAMING_MODE					22
#define			HES_BAD_ANGLE							23
#define			HES_BAD_BLOCKING_FACTOR					24
#define			HES_BAD_BOUNCE_LIMIT					25
#define			HES_BAD_CHARACTER						26
#define			HES_BAD_COLOR_CONSOLIDATION				27
#define			HES_BAD_CONCENTRATION					28
#define			HES_BAD_DEFINITION						29
#define			HES_BAD_EDGE_SHARPNESS_ANGLE			30
#define			HES_BAD_EDGE_SHARPNESS_FRU				31
#define			HES_BAD_EDGE_SHARPNESS_PERCENT			32
#define			HES_BAD_FIELD_HEIGHT					33
#define			HES_BAD_FIELD_WIDTH						34
#define			HES_BAD_FIRST_COLOR						35
#define			HES_BAD_FIXED_COLORS_SPEC				36
#define			HES_BAD_ILLUMINATION_ANGLE				37
#define			HES_BAD_ILLUMINATION_FRU				38
#define			HES_BAD_LENGTH							39
#define			HES_BAD_NUMBER_OF_COLORS				40
#define			HES_BAD_OBLIQUE_PROJECTION				41
#define			HES_BAD_PARENTHESES						42
#define			HES_BAD_PEN_SPEED						43
#define			HES_BAD_PERSPECTIVE						44
#define			HES_BAD_PHYSICAL_SIZE					45
#define			HES_BAD_POSITION						46
#define			HES_BAD_REFERENCE_POINT					47
#define			HES_BAD_RETURN_KEY						48
#define			HES_BAD_SELECTION_PROXIMITY				49
#define			HES_BAD_SIZE_LIMIT						50
#define			HES_BAD_SUB_DIVISION_NUMBER				51
#define			HES_BAD_TEXT_PATH						52
#define			HES_BAD_TEXT_SCALE_FACTOR				53
#define			HES_BAD_TEXT_SLANT						54
#define			HES_BAD_UP_VECTOR						55
#define			HES_BAD_VALUE							56
#define			HES_BAD_WINDOW_SCOPE					57
#define			HES_BAD_XMIN							58
#define			HES_BAD_YMIN							59
#define			HES_BASE_COLOR_OVERRIDE					60
#define			HES_BEGINS_WITH_QUESTION_MARK			61
#define			HES_BEHIND_THE_EYE						62
#define			HES_BIG_ENDIAN_SHOULD_BE_FALSE			63
#define			HES_BIG_ENDIAN_SHOULD_BE_TRUE			64
#define			HES_BOUNDING_BOX						65
#define			HES_BUTTON_EVENT_NOT_ENABLED			66
#define			HES_CALLBACK							67
#define			HES_CAMERA								68
#define			HES_CAMERA_IGNORED						69
#define			HES_CANNOT_ALLOCATE_X_COLOR_CELLS		70
#define			HES_CANNOT_CHANGE_OPTION				71
#define			HES_CANNOT_CLOSE_SEGMENT				72
#define			HES_CANNOT_CREATE_WINDOW				73
#define			HES_CANNOT_DESTROY_WORLD				74
#define			HES_CANNOT_EDIT_BLOCK_TEXT				75
#define			HES_CANNOT_FLUSH_WRITE_BUFFER			76
#define			HES_CANNOT_OPEN_DEVICE					77
#define			HES_CANNOT_OPEN_DISPLAY					78
#define			HES_CANNOT_OPEN_UNNAMED_SEGMENT			79
#define			HES_CANNOT_QUICK_MOVE_IMAGE				80
#define			HES_CANNOT_QUICK_MOVE_LIT_FACE			81
#define			HES_CANNOT_SCROLL						82
#define			HES_CANNOT_SET_ATTRIBUTE				83
#define			HES_CANNOT_START_PEX_SERVER				84
#define			HES_CANNOT_UNSET_ATTRIBUTE				85
#define			HES_CLEAR_WINDOW_INHERITED				86
#define			HES_CMAP_FULL_REQUIRED					87
#define			HES_COINCIDENT_POINT					88
#define			HES_COLINEAR_POINTS						89
#define			HES_COLOR								90
#define			HES_COLOR_COMPONENTS_MISMATCH			91
#define			HES_COLOR_INDEX_IGNORED					92
#define			HES_COLOR_MAP_DEVICE_FAILED				93
#define			HES_COLOR_WAS_NOT_SET_BY_INDEX			94
#define			HES_COLOR_WAS_SET_BY_INDEX				95
#define			HES_COMPILER_LIMITATION					96
#define			HES_COMPLEX_COLOR						97
#define			HES_COMPUTE								98
#define			HES_COMPUTE_CONTEXT_FAILED				99
#define			HES_COMPUTE_VISUALINFO_FAILED			100
#define			HES_CREATE_CONTEXT_FAILED				101
#define			HES_CREATE_GRAPHICS_CONTEXT_FAILED		102
#define			HES_CREATE_LINE_PATTERN_FAILED			103
#define			HES_CREATE_MEMORY_RASTER_FAILED			104
#define			HES_CREATE_MULTIBUFFER_FAILED			105
#define			HES_CREATE_STIPPLES_FAILED				106
#define			HES_CREATE_WINDOW_FAILED				107
#define			HES_CREATE_WINDOW_RASTER_FAILED			108
#define			HES_CURSOR_ALREADY_PRESENT				109
#define			HES_CURSOR_DELETED						110
#define			HES_CUTTING_PLANE						111
#define			HES_DATA_LENGTH_MISMATCH				112
#define			HES_DEAD_DRIVER							113
#define			HES_DEFAULT_WORLD_ATTRIBUTE				114
#define			HES_DEFINITION_NOT_FOUND				115
#define			HES_DEGENERATE_DEFINITION				116
#define			HES_DELETED_CURSOR						117
#define			HES_DELETED_DISPLAY						118
#define			HES_DELETED_ITEM						119
#define			HES_DELETED_KEYBOARD					120
#define			HES_DELETED_LOCATOR						121
#define			HES_DELETE_FONT_WITH_ESCAPEMENT			122
#define			HES_DIRECTION_IS_SINGULAR				123
#define			HES_DIRECTORY_CLOSE						124
#define			HES_DIRECTORY_OPEN						125
#define			HES_DIRECTORY_READ						126
#define			HES_DISK_FULL							127
#define			HES_DISTANT_LIGHT						128
#define			HES_DRIVER								129
#define			HES_DRIVER_ATTRIBUTE_ABSENT				130
#define			HES_DRIVER_ATTRIBUTE_MISSING			131
#define			HES_DUPLICATE_DEFINITION				132
#define			HES_EDGE								133
#define			HES_EDGE_AND_FACE_SEL_MISMATCH			134
#define			HES_EDGE_AND_FACE_VIS_MISMATCH			135
#define			HES_ENABLE_MOUSE_KEYBOARD_EVENT			136
#define			HES_ENCODING_NOT_IMPLEMENTED			137
#define			HES_END_WITHOUT_BEGIN_SEARCH			138
#define			HES_ERROR_RESTORING_TIMER				139
#define			HES_ERROR_SETTING_TIMER					140
#define			HES_ERROR_STARTING_DRIVER				141
#define			HES_ERROR_SUSPENDING_TIMER				142
#define			HES_ERROR_WRITING_FILE					143
#define			HES_EVENT_CHECKER						144
#define			HES_EXTDEVICEMODE_NOT_SUPPORTED			145
#define			HES_EXTREME_ANGLE						146
#define			HES_FACE								147
#define			HES_FACE_OR_VERTEX_ONLY					148
#define			HES_FATAL_ERROR							149
#define			HES_FILE_IO								150
#define			HES_FILE_OPEN							151
#define			HES_FIND_FONT_WITH_ESCAPEMENT			152
#define			HES_FIRST_COLOR_IGNORED					153
#define			HES_FONT_CHARACTER						154
#define			HES_FONT_CHARACTERS_NOT_RECORDED		155
#define			HES_FONT_FILE_SEARCH					156
#define			HES_GENERAL_ERROR						157
#define			HES_GEOMETRY							158
#define			HES_GEOMETRY_NOT_CREATED_BY_IM			159
#define			HES_GETIMAGE_FOR_TEXT_FAILED			160
#define			HES_GET_OUTER_WINDOW					161
#define			HES_GLXMAKECURRENT_FAILED				162
#define			HES_GLX_EXTENSIONS_NOT_PRESENT			163
#define			HES_HARDWARE_Z_BUFFER_DEPTH				164
#define			HES_HOOPS_IS_CONFUSED					165
#define			HES_HOOPS_PICTURE_UNDEFINED				166
#define			HES_IMAGE								167
#define			HES_IMAGE_MISSING						168
#define			HES_IM_MISMATCH							169
#define			HES_IM_NOT_PRESENT						170
#define			HES_INACTIVE_SEARCH						171
#define			HES_INFINITE_LOOP						172
#define			HES_INSUFFICIENT_TEXT_INFO				173
#define			HES_INVALID_ACTION_NAME					174
#define			HES_INVALID_ADDRESS_POINTER				175
#define			HES_INVALID_CHARACTER					176
#define			HES_INVALID_CHARACTER_NUMBER			177
#define			HES_INVALID_COLOR_SPACE					178
#define			HES_INVALID_COLUMN						179
#define			HES_INVALID_COORDINATE_SPACE			180
#define			HES_INVALID_COUNT						181
#define			HES_INVALID_DEF_FONT_DRAW_CODE			182
#define			HES_INVALID_DELETE_COUNT				183
#define			HES_INVALID_DIRECTION					184
#define			HES_INVALID_ENCODING					185
#define			HES_INVALID_ERASE_COUNT					186
#define			HES_INVALID_FACE_COUNT					187
#define			HES_INVALID_FACE_OFFSET					188
#define			HES_INVALID_FACE_RANGE					189
#define			HES_INVALID_FILL_PATTERN_SIZE			190
#define			HES_INVALID_FIRST_COLOR					191
#define			HES_INVALID_FONT_FILE					192
#define			HES_INVALID_FOR_CUTTING_PLANES			193
#define			HES_INVALID_GEOMETRY_OR_INCLUDE			194
#define			HES_INVALID_GEOMETY_OR_SEGMENT			195
#define			HES_INVALID_HEIGHT						196
#define			HES_INVALID_IMAGE						197
#define			HES_INVALID_INDEX						198
#define			HES_INVALID_INPUT						199
#define			HES_INVALID_INSERT_COUNT				200
#define			HES_INVALID_INTERVAL					201
#define			HES_INVALID_KEY							202
#define			HES_INVALID_LICENSE						203
#define			HES_INVALID_LIST_LENGTH					204
#define			HES_INVALID_NUMBER						205
#define			HES_INVALID_NUMBER_OF_ARGUMENTS			206
#define			HES_INVALID_OFFSET						207
#define			HES_INVALID_OPEN						208
#define			HES_INVALID_OPTION						209
#define			HES_INVALID_OUTPUT						210
#define			HES_INVALID_PATH_TOKEN					211
#define			HES_INVALID_PEN_MAP_VALUE				212
#define			HES_INVALID_PROJECTION					213
#define			HES_INVALID_RANGE						214
#define			HES_INVALID_REFERENCE					215
#define			HES_INVALID_RELATED_EVENT				216
#define			HES_INVALID_REVISION					217
#define			HES_INVALID_ROTATION_AXIS				218
#define			HES_INVALID_ROW							219
#define			HES_INVALID_SEG_NAME_PARAMETER			220
#define			HES_INVALID_SELECTION_PROXIMITY			221
#define			HES_INVALID_SIZE						222
#define			HES_INVALID_STRING_CURSOR				223
#define			HES_INVALID_SUBSCREEN_SPEC				224
#define			HES_INVALID_TARGET						225
#define			HES_INVALID_TEXT_ENCODING				226
#define			HES_INVALID_TOLERENCE					227
#define			HES_INVALID_TRANSFORM_SEGMENT			228
#define			HES_INVALID_TYPE						229
#define			HES_INVALID_VISUAL						230
#define			HES_INVALID_VISUAL_CLASS				231
#define			HES_INVALID_WEIGHT						232
#define			HES_INVALID_WIDTH						233
#define			HES_INVALID_WIDTH_OR_HEIGHT				234
#define			HES_INVALID_ZOOM_FACTOR					235
#define			HES_JUMP_TO_INVALID_CODE_LINK			236
#define			HES_LIGHT								237
#define			HES_LOAD_FONT							238
#define			HES_LOAD_FONT_FAILED					239
#define			HES_LOAD_XGL_FONT_FAILED				240
#define			HES_LOCATION							241
#define			HES_LOCATION_EVENT_NOT_ENABLED			242
#define			HES_LOCATOR_WITHOUT_DISPLAY				243
#define			HES_LOGICAL_NAME_TRANSLATION			244
#define			HES_MAIN_WINDOW_ID_MISSING				245
#define			HES_MARKER								246
#define			HES_MARK_FONT_DEFAULT_FAILED			247
#define			HES_MARK_FONT_GENERIC_FAILED			248
#define			HES_MARK_FONT_ROTATEABLE_FAILED			249
#define			HES_MAY_NOT_HAVE_TEXTURES				250
#define			HES_MEMORY_PURGED						251
#define			HES_MOST_RECENT_OPEN					252
#define			HES_MULTIPLE_OCCURANCES					253
#define			HES_NONE_FOUND							254
#define			HES_NON_SQUARE_PIXELS					255
#define			HES_NON_UNIFORM_HANDEDNESS				256
#define			HES_NORMAL								257
#define			HES_NOT_AVAILABLE						258
#define			HES_NOT_A_CAMERA_VOLUME					259
#define			HES_NOT_A_DIRECT_DESCENDANT				260
#define			HES_NOT_PRESENT							261
#define			HES_NOT_VALID_FOR_WINDOWS				262
#define			HES_NO_ACTIVE_DISPLAY					263
#define			HES_NO_ACTIVE_DISPLAY_DRIVER			264
#define			HES_NO_COLOR_TYPE_FOR_DISPLAY			265
#define			HES_NO_DIFFUSE_COLOR_COMPONENT			266
#define			HES_NO_LOCAL_SETTING					267
#define			HES_NO_MAPPED_VISAUL_TYPE				268
#define			HES_NO_OPEN_SEGMENT						269
#define			HES_NO_X_WINDOW_FOR_GL_WINDOW			270
#define			HES_NULL_COLOR_NAME						271
#define			HES_NULL_INPUT							272
#define			HES_NUMBER_ALREADY_IN_USE				273
#define			HES_OBSOLETE_FUNCTION					274
#define			HES_OBSOLETE_USAGE						275
#define			HES_ONE_INFO_ITEM_ONLY					276
#define			HES_OPEN_EDGE_ONLY						277
#define			HES_OPEN_FACE_ONLY						278
#define			HES_OPEN_FACE_OR_VERTEX_ONLY			279
#define			HES_OPEN_GEOMETRY						280
#define			HES_OPEN_GEOMETRY_FIRST					281
#define			HES_OPEN_SEGMENT						282
#define			HES_OPEN_TRISTRIP_ONLY					283
#define			HES_OPEN_VERTEX_ONLY					284
#define			HES_ORPHAN_SEGMENT						285
#define			HES_OUTER_MOST_WINDOW_IS_CLEAR			286
#define			HES_OUTPUT_SEGMENT_EXISTS				287
#define			HES_OUT_OF_RANGE						288
#define			HES_OUT_OF_RANGE_BLUE					289
#define			HES_OUT_OF_RANGE_CHROMACITY				290
#define			HES_OUT_OF_RANGE_COLOR_INDEX			291
#define			HES_OUT_OF_RANGE_COLOR_MAP				292
#define			HES_OUT_OF_RANGE_GREEN					293
#define			HES_OUT_OF_RANGE_HUE					294
#define			HES_OUT_OF_RANGE_LIGHTNESS				295
#define			HES_OUT_OF_RANGE_MESSAGE_LIMIT			296
#define			HES_OUT_OF_RANGE_NUMBER					297
#define			HES_OUT_OF_RANGE_PEN_MAP				298
#define			HES_OUT_OF_RANGE_RED					299
#define			HES_OUT_OF_RANGE_RGB					300
#define			HES_OUT_OF_RANGE_SATURATION				301
#define			HES_OUT_OF_RANGE_STRING_HISTORY			302
#define			HES_OUT_OF_RANGE_STRING_LENGTH			303
#define			HES_OUT_OF_RANGE_VALUE_SCALE			304
#define			HES_OUT_OF_RANGE_WINDOW					305
#define			HES_OVERLAY_MODE_NOT_SUPPORTED			306
#define			HES_OVERLAY_WINDOW_ID_MISSING			307
#define			HES_PARAMETER							308
#define			HES_PARSE_STRING						309
#define			HES_PATTERN								310
#define			HES_PLAIN_TEXTURE_ONLY					311
#define			HES_POLYGON								312
#define			HES_POLYLINE							313
#define			HES_PRINT_VERSION_MESSAGE				314
#define			HES_PURE_COLOR_OR_TEXTURE_ONLY			315
#define			HES_REBUILDING_TRISTRIP					316
#define			HES_RECEIVED_EXIT_REQUEST				317
#define			HES_REDEFINING_NAME						318
#define			HES_RENDITION_FREED						319
#define			HES_RENDITION_NOT_FREED					320
#define			HES_REPLACEMENT_OVERFLOW				321
#define			HES_REQUIRES_COLOR_MAP					322
#define			HES_RGB_TYPE_IMAGE_REQUIRED				323
#define			HES_SEGMENT								324
#define			HES_SEGMENT_EXISTS						325
#define			HES_SELECTION_EVENT_NOT_ENABLED			326
#define			HES_SELF_INTERSECTING_FACE				327
#define			HES_SET_SB_X_SHARED_CMAP_ENV_VAR		328
#define			HES_SINGULAR_MATRIX						329
#define			HES_SINGULAR_PLANE						330
#define			HES_SIZE								331
#define			HES_SMALL_FIXED_COLORS					332
#define			HES_SMALL_NUMBER_OF_COLORS				333
#define			HES_SPOOL_SPACE							334
#define			HES_STACK_MODE_NOT_SUPPORTED			335
#define			HES_STARBASE_ERROR						336
#define			HES_STARBASE_X_CONNECTION_FAILED		337
#define			HES_STATICCOLOR_INDEX_FAILED			338
#define			HES_STRING_CURSOR						339
#define			HES_STRING_CURSOR_DISABLED				340
#define			HES_STRING_CURSOR_MISMATCH				341
#define			HES_STRING_EVENT_NOT_ENABLED			342
#define			HES_SYMBOL								343
#define			HES_SYNTAX_ERROR						344
#define			HES_SYSTEM_OPTION_EXCEEDED				345
#define			HES_SYSTEM_STATE_OBJECT_FAILED			346
#define			HES_TARGET								347
#define			HES_TARGET_LOCATOR_CONNECTED			348
#define			HES_TARGET_LOCATOR_NOT_CONNECTED		349
#define			HES_TEXT								350
#define			HES_TEXT_OWNS_STRING_CURSOR				351
#define			HES_TEXT_WITH_RENDITION					352
#define			HES_TOO_MANY_COLORS						353
#define			HES_TOO_MANY_EXIT_HANDLERS				354
#define			HES_TOO_MANY_FIXED_COLORS				355
#define			HES_TOO_MANY_PATTERNS					356
#define			HES_TRANSFORM_ENGINE_ERROR				357
#define			HES_TRISTRIP							358
#define			HES_TRISTRIP_ONLY						359
#define			HES_UIS_SOFTWARE_NOT_AVAILABLE			360
#define			HES_UNAVAILABLE_VISUAL_CLASS			361
#define			HES_UNDEFINE_ERROR_HANDLER				362
#define			HES_UNDEFINE_EXIT_HANDLER				363
#define			HES_UNDEFINE_FAILED						364
#define			HES_UNDEFINE_NOT_ALLOWED				365
#define			HES_UNSUPPORTED_PARAM_SOURCE			366
#define			HES_USE_SHOW_ONE_COLOR					367
#define			HES_USE_SHOW_ONE_TEXT_FONT				368
#define			HES_USING_DEFAULT_VISUAL				369
#define			HES_USING_SB_OUTDRIVER					370
#define			HES_VERSION_MISMATCH					371
#define			HES_VISIBILITY							372
#define			HES_VISUAL_FOR_OPENGL_MISSING			373
#define			HES_WAKEUP_NOT_ENABLED					374
#define			HES_WEIGHT								375
#define			HES_WINDOW								376
#define			HES_WINDOWS_FONT						377
#define			HES_WINDOW_ID_REPLACED					378
#define			HES_WORKS_WITH_RENUMBERED_KEY			379
#define			HES_WRITE_BYTE_TO_FILE_FAILED			380
#define			HES_WRITE_FAILED						381
#define			HES_WRONG_DRIVER_TYPE_ON_X11			382
#define			HES_X11_FATAL_IO_ERROR					383
#define			HES_X11_SYSTEM_ERROR					384
#define			HES_X_TO_GL_BIND_FAILED					385
#define			HES_ZERO_LENGTH							386
#define			HES_Z_BUFFERED_IMAGE					387

#define			HES_DOUBLE_BUFFER_REQUEST_FAILED				388
#define			HES_DOUBLE_BUFFER_WITH_SOFTWARE_Z_BUFFER		389
#define			HES_DRIVER_NOT_LOADED							390
#define			HES_EXIT_HANDLER_INSTALL_FAILED					391
#define			HES_FILE_CLOSE									392
#define			HES_FORCEBW_WITH_SOFTWARE_Z_BUFFER				393
#define			HES_GRAPHICS_ADAPTER							394
#define			HES_INVALID_CURSOR_STYLE						395
#define			HES_FONT_MARK_AS_DEFAULT_FAILED					396
#define			HES_FONT_MARK_AS_GENERIC_FAILED					397
#define			HES_FONT_MARK_AS_ROTATE_FAILED					398
#define			HES_INCOMPATIBLE_TABLET_DRIVER					399
#define			HES_ONLY_DIFFUSE_COLOR_COMPONENT				400
#define			HES_REINITIALIZE_FAILED							401
#define			HES_UNSUPPORTED_DEVICE							402
#define			HES_VMM_LOCK_FAILED								403
#define			HES_VMM_UNLOCK_FAILED							404
#define			HES_XGL_ERROR									405
#define			HES_NOWINDOWHOOK_COLORMAPID_REQUIRED_TOGETHER	406
#define			HES_MDI_SUPPORTED_BY_NOWINDOWSHOOK				407

#define			HES_OPEN_SHELL_OR_MESH_ONLY						408
#define			HES_NEGATIVE_OFFSET								409
#define			HES_ZERO_OFFSET							410
#define			HES_DISPLAY_LIST_PROBLEM				411

#define			HES_REGION								412
#define			HES_DRIVER_NOT_ISOLATED					413
#define			HES_REDUNDANT							414
#define			HES_FALLBACK_TO_STROKED					415

#define			HES_IGNORED								416
#define			HES_MISSING								417

#define			HES_CONDITIONAL							418
#define			HES_EXTERNAL							419

#define			HES_NONWINDOWED_HSR						420

#define HOOPS_ERRORS_DEFINED
#endif /* HOOPS_ERRORS_DEFINED */
