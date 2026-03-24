/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a 
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.5 2010-10-26 18:34:48 evan Exp $
 */

#if defined(COCOA_OGL_DRIVER) || defined(_hoops_AIAGA)

@interface _hoops_PIAGA : NSOpenGLView
{
	
}

- (void) drawRect: (NSRect) _hoops_RCHS;

- (NSPoint) convert_mouse_location: (NSEvent *) _hoops_HIAGA;
- (NSPoint) consume_mouse: (NSEvent *) _hoops_HIAGA;
- (void) mouseDown: (NSEvent *) _hoops_HIAGA;
- (void) mouseUp: (NSEvent *) _hoops_HIAGA;
- (void) mouseDragged: (NSEvent *) _hoops_HIAGA;
- (void) keyDown: (NSEvent *) _hoops_HIAGA;
- (void) reshape;

- (BOOL) acceptsFirstResponder;
- (BOOL) becomeFirstResponder;
- (BOOL) resignFirstResponder;

- (id)initWithCoder:(NSCoder *)_hoops_IIAGA;
- (void)encodeWithCoder:(NSCoder *)_hoops_CIAGA;

- (BOOL)acceptsFirstMouse:(NSEvent *)_hoops_HIAGA;
- (void) dealloc;

@end

#define _hoops_RRRRR				0x01
#define _hoops_PRRRR			0x04
#define	_hoops_ARRRR				0x02

#define B_SHIFT					0x00000100
#define B_CONTROL				0x00000200 
#define B_NUM_LOCK				0x00000400
#define B_ALT					0x00000800
#define B_CAPS_LOCK				0x00001000
#define B_SCROLL_LOCK			0x00002000
#define B_LEFT_SHIFT			0x00004000
#define B_RIGB_SHIFT			0x00008000
#define B_RIGB_CONTROL			0x00010000
#define B_LEFT_CONTROL			0x00020000
#define B_RIGB_ALT				0x00040000
#define B_LEFT_ALT				0x00080000

@implementation _hoops_PIAGA

-(void) drawRect: (NSRect) _hoops_RCHS {
	
	//_hoops_IPRPR("_hoops_SIAGA _hoops_GCAGA\_hoops_ACHP");
	
	Display_Context *dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT)self);
	
	if (dc)
		HD_Force_Refresh(dc);	
	
	//[_hoops_RCAGA _hoops_GCAGA:_hoops_PRCH];
}

- (void) reshape {
	
	Display_Context *dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT)self);
	
	if (dc) {
		
		OGLDATA *_hoops_CSRGR = ((OGLDATA alter *)((dc)->_hoops_RIHGR));
		
		NSRect frame = [self frame];
		
		_hoops_CSRGR->yfudge = frame.size.height -1;
		HD_Resize_Subscreen(dc, true, 0, frame.size.width - 1, 0, frame.size.height - 1);	
		HD_Force_Refresh(dc);
	}
}

- (NSPoint) convert_mouse_location: (NSEvent *) _hoops_HIAGA {
	
	NSPoint _hoops_ACAGA = [_hoops_HIAGA locationInWindow];
	NSPoint _hoops_PCAGA = [self convertPoint:_hoops_ACAGA fromView:nil];
	
	NSRect frame = [self frame];
	
	NSPoint _hoops_HCAGA;
	_hoops_HCAGA.x = _hoops_PCAGA.x;
	_hoops_HCAGA.y = frame.size.height - _hoops_PCAGA.y;
	
	return _hoops_HCAGA;	
}

- (NSPoint) consume_mouse: (NSEvent *) _hoops_HIAGA {
	
	Display_Context *dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT)self);
	OGLDATA *_hoops_CSRGR = ((OGLDATA alter *)((dc)->_hoops_RIHGR));   	 
	
	NSEventType type = [_hoops_HIAGA type];	
	
	switch (type) {
			
		case NSLeftMouseDown: _hoops_CSRGR->_hoops_HRRRR |= _hoops_RRRRR; break;			
		case NSRightMouseDown: _hoops_CSRGR->_hoops_HRRRR |= _hoops_ARRRR; break;
		case NSLeftMouseUp: _hoops_CSRGR->_hoops_HRRRR &= ~_hoops_RRRRR; break;			
		case NSRightMouseUp: _hoops_CSRGR->_hoops_HRRRR &= ~_hoops_ARRRR; break;
		case NSLeftMouseDragged: _hoops_CSRGR->_hoops_HRRRR |= _hoops_RRRRR; break;	
		case NSRightMouseDragged: _hoops_CSRGR->_hoops_HRRRR |= _hoops_ARRRR; break;
			
		default: printf("not handling some mouse event\n"); break;		
	}
	
	NSPoint _hoops_ICAGA = [self convert_mouse_location:_hoops_HIAGA];
	_hoops_ICAGA.y = _hoops_CSRGR->yfudge - _hoops_ICAGA.y;
	
	_hoops_CSRGR->_hoops_SCGRR = _hoops_ICAGA.x;
	_hoops_CSRGR->mouse_y = _hoops_ICAGA.y;		
	
	HD_Queue_Pixel_Location_Event (_hoops_CSRGR->dc, 
								   _hoops_CSRGR->_hoops_HRRRR,
								   _hoops_CSRGR->_hoops_SCGRR,
								   _hoops_CSRGR->mouse_y);
	
	_hoops_CSRGR->_hoops_IRRRR = true;
	
	return _hoops_ICAGA;
}

- (void)mouseDown: (NSEvent *) _hoops_HIAGA {	
	
	NSPoint loc = [self consume_mouse : _hoops_HIAGA];
	//_hoops_IPRPR("_hoops_SIAGA _hoops_CCAGA, _hoops_SISR = %_hoops_HAS, _hoops_HAPC = %_hoops_HAS\_hoops_ACHP",(_hoops_SCSH)_hoops_SCAGA._hoops_SISR,(_hoops_SCSH)_hoops_SCAGA._hoops_HAPC);
}

- (void)mouseUp: (NSEvent *) _hoops_HIAGA {
	NSPoint loc = [self consume_mouse : _hoops_HIAGA];
	//_hoops_IPRPR("_hoops_SIAGA _hoops_GSAGA, _hoops_SISR = %_hoops_HAS, _hoops_HAPC = %_hoops_HAS\_hoops_ACHP",(_hoops_SCSH)_hoops_SCAGA._hoops_SISR,(_hoops_SCSH)_hoops_SCAGA._hoops_HAPC);
}

- (void)mouseDragged: (NSEvent *) _hoops_HIAGA {
	NSPoint loc = [self consume_mouse : _hoops_HIAGA];
	//_hoops_IPRPR("_hoops_SIAGA _hoops_RSAGA, _hoops_SISR = %_hoops_HAS, _hoops_HAPC = %_hoops_HAS\_hoops_ACHP",(_hoops_SCSH)_hoops_SCAGA._hoops_SISR,(_hoops_SCSH)_hoops_SCAGA._hoops_HAPC);
}

- (void) keyDown: (NSEvent *) _hoops_HIAGA {	
	
	Display_Context *dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT)self);
	OGLDATA *_hoops_CSRGR = ((OGLDATA alter *)((dc)->_hoops_RIHGR));
	
	NSUInteger _hoops_ASAGA;
	NSUInteger key_mod;
	NSUInteger key;
	int status = 0;	
	
	_hoops_ASAGA = [_hoops_HIAGA keyCode];
	key_mod = [_hoops_HIAGA modifierFlags];
	
	if (key_mod & NSShiftKeyMask) {
		status |= B_SHIFT;
	}
	if (key_mod & NSControlKeyMask) {
		status |= B_CONTROL;
	}
	if (key_mod & NSAlternateKeyMask) {
		status |= B_ALT;
	}
	
	/*
	 	 
	 _hoops_SIGP:
	 
	 _hoops_RPP (_hoops_PSAGA &&) _hoops_HSAGA |= _hoops_ISAGA;
	 _hoops_RPP (_hoops_PSAGA &&) _hoops_HSAGA |= _hoops_CSAGA;
	 _hoops_RPP (_hoops_PSAGA &&) _hoops_HSAGA |= _hoops_SSAGA;
	 */
	
	//_hoops_SIC = _hoops_GGPGA((_hoops_SRPC *)_hoops_RGPGA(_hoops_AGPGA), 
	//				   _hoops_PSAGA | _hoops_PGPGA, &_hoops_HGPGA->_hoops_IGPGA);
	
	// 
	
	/*
	 _hoops_CICA (_hoops_SIC) {
	 _hoops_AGIR _hoops_CGPGA:			_hoops_SIC = _hoops_SGPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_GRPGA:			_hoops_SIC = _hoops_RRPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_ARPGA:		_hoops_SIC = _hoops_PRPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_HRPGA:			_hoops_SIC = _hoops_IRPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_CRPGA:		_hoops_SIC = _hoops_SRPGA; _hoops_IHSA;
	 
	 _hoops_AGIR _hoops_GAPGA:	_hoops_SIC = _hoops_RAPGA; _hoops_IHSA;
	 
	 _hoops_AGIR _hoops_AAPGA:	_hoops_SIC = _hoops_PAPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_HAPGA:	_hoops_SIC = _hoops_IAPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_CAPGA:		_hoops_SIC = _hoops_SAPGA; _hoops_IHSA;
	 _hoops_AGIR _hoops_GPPGA:	_hoops_SIC = _hoops_RPPGA; _hoops_IHSA;
	 _hoops_SHIR:_hoops_IHSA;
	 }
	 */
	
	if ((key_mod & 0x00010000L) && (key >= '0' && key<= '9')) {
		key = FIRST_KEYPAD_KEY + key - '0';
	}
	
	NSString *_hoops_APPGA = [_hoops_HIAGA characters];
	key = [_hoops_APPGA characterAtIndex:0];
	//_hoops_IPRPR("_hoops_SIAGA _hoops_PPPGA, _hoops_SIC = %_hoops_GSGGR \_hoops_ACHP",(_hoops_GSPR)_hoops_SIC);
	
	HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)_hoops_CSRGR->dc->_hoops_GHRI, key, status);	
}

- (void)dealloc {	
	//_hoops_IPRPR("_hoops_SIAGA _hoops_HPPGA\_hoops_ACHP");	 
    [super dealloc];		
}

- (BOOL)acceptsFirstResponder {	
    return YES;		
}

- (BOOL) becomeFirstResponder {
	return YES;
}

- (BOOL) resignFirstResponder {
	return YES;
}

- (BOOL)acceptsFirstMouse:(NSEvent *)_hoops_HIAGA {
	return YES;
}

- (id)initWithCoder:(NSCoder *)_hoops_IIAGA {	
	return [super initWithCoder:_hoops_IIAGA];	
}

- (void)encodeWithCoder:(NSCoder *)_hoops_CIAGA {	
	[super encodeWithCoder:_hoops_CIAGA];	
}

@end

#undef OGLDATA
#undef _hoops_PIAGA

template <class OGLDATA, class _hoops_IPPGA>
local POINTER_SIZED_INT create_standalone_window(Display_Context * dc) {
	
	OGLDATA alter *_hoops_CSRGR = (OGLDATA alter *)dc->_hoops_RIHGR;	
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];	
    
	{
		BOOL error = NSApplicationLoad();    
		assert(error == YES);    
	}
	
	// [_hoops_CPPGA _hoops_SPPGA : _hoops_GHPGA];  
    
	Rect rect;	
	rect.left = dc->_hoops_RHPGA.left;
	rect.right = dc->_hoops_RHPGA.right;
	rect.top = _hoops_CSRGR->_hoops_CCGRR - dc->_hoops_RHPGA.top;
	rect.bottom = _hoops_CSRGR->_hoops_CCGRR - dc->_hoops_RHPGA.bottom;
	
	_hoops_CSRGR->_hoops_ISIH = (float)(rect.right-rect.left)/(float)(rect.bottom-rect.top);
	
	NSRect frame = NSMakeRect(0,0,rect.right-rect.left,rect.bottom-rect.top);
	//_hoops_AHPGA _hoops_HCHSR = _hoops_PHPGA(0,0,1024,768);
	
	char temp[4096];
    strcat(temp,"unnamed window");
    
	HI_Copy_Name_To_Chars (&dc->options._hoops_IAPIR, temp);	
	NSString *_hoops_IAPIR = [NSString stringWithUTF8String : temp];
	
	NSWindow *window  = [[NSWindow alloc] initWithContentRect : frame
													styleMask : NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
													  backing : NSBackingStoreBuffered
														defer : false];
	
	[window setTitle: _hoops_IAPIR];
	[window setReleasedWhenClosed: NO];	
	//[_hoops_RPPS _hoops_HHPGA: _hoops_GHPGA];	
	
	_hoops_IPPGA *_hoops_IHPGA = [[_hoops_IPPGA alloc]	initWithFrame : frame
                                  pixelFormat : [NSOpenGLView defaultPixelFormat]];
	
	unsigned int mask = NSViewWidthSizable | NSViewHeightSizable;
	[_hoops_IHPGA setAutoresizingMask:mask];
	
	[window	setContentView: _hoops_IHPGA]; 
	{
		BOOL error = [window makeFirstResponder: _hoops_IHPGA];
		assert(error == YES);
	}
    
	_hoops_CSRGR->_hoops_IHPGA = _hoops_IHPGA;
	_hoops_CSRGR->window = window;	
	
	[pool drain];	 	
	
	return (POINTER_SIZED_INT)_hoops_CSRGR->_hoops_IHPGA;
}

template <class T>
local void check_events(T *_hoops_CSRGR) {
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];		
	
	NSUInteger mask = NSAnyEventMask;		
	NSEvent *event = 0;
	
	_hoops_CSRGR->_hoops_IRRRR = false;
	
	while (event = [NSApp nextEventMatchingMask:mask 
									  untilDate:nil 
										 inMode:NSDefaultRunLoopMode
										dequeue:YES]) {		
        
        [NSApp sendEvent : event]; 	
	}
	
	[pool drain];
}


template <class OGLDATA>
local POINTER_SIZED_INT _hoops_CHPGA(Display_Context *dc) {
	
	OGLDATA *_hoops_CSRGR = ((OGLDATA alter *)((dc)->_hoops_RIHGR));
	
	NSOpenGLPixelBuffer  *pbuffer = [[NSOpenGLPixelBuffer alloc] initWithTextureTarget: GL_TEXTURE_RECTANGLE_ARB
																 textureInternalFormat:GL_RGBA
																 textureMaxMipMapLevel: 0
																			pixelsWide:_hoops_CSRGR->_hoops_IHGRR->width
																			pixelsHigh:_hoops_CSRGR->_hoops_IHGRR->height];	
	
	_hoops_CSRGR->pbuffer = pbuffer;
	
	return (POINTER_SIZED_INT)pbuffer;	
}	

template <class OGLDATA>
local Rect _hoops_SHPGA(Display_Context const * dc) {
	
	OGLDATA *_hoops_CSRGR = ((OGLDATA alter *)((dc)->_hoops_RIHGR));
	NSView *_hoops_IHPGA = _hoops_CSRGR->_hoops_IHPGA;
	NSRect frame = [_hoops_IHPGA frame];
	Rect rect;
	
	rect.left = frame.origin.x;
	rect.right = frame.origin.x + frame.size.width;
	rect.top = frame.origin.y;
	rect.bottom = frame.origin.y + frame.size.height;
	
	return rect;
}


template <class OGLDATA>
local void choose_pixel_format(Display_Context * dc)
{
	OGLDATA *_hoops_CSRGR = ((OGLDATA alter *)((dc)->_hoops_RIHGR));
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	int i = 0;
	GLuint _hoops_GIPGA[32];
	
	_hoops_GIPGA[i++] = NSOpenGLPFAAccelerated;	
	_hoops_GIPGA[i++] = NSOpenGLPFAWindow;	
	_hoops_GIPGA[i++] = NSOpenGLPFAPixelBuffer;	
	_hoops_GIPGA[i++] = NSOpenGLPFAColorSize;
	_hoops_GIPGA[i++] = 24;	
	_hoops_GIPGA[i++] = NSOpenGLPFADepthSize;
	_hoops_GIPGA[i++] = 24;
	
	if (dc->options._hoops_SRRRR) {
		_hoops_GIPGA[i++] = NSOpenGLPFADoubleBuffer;
		_hoops_GIPGA[i++] = NSOpenGLPFABackingStore;
	}
	
	if (dc->options._hoops_RIPGA && dc->options._hoops_AIPGA != 0) {
		
		_hoops_GIPGA[i++] = NSOpenGLPFAMultisample;
		_hoops_GIPGA[i++] = NSOpenGLPFASampleBuffers;
		_hoops_GIPGA[i++] = (NSOpenGLPixelFormatAttribute)1;
		_hoops_GIPGA[i++] = NSOpenGLPFASamples;			
		
		if (dc->options._hoops_AIPGA < 0)
			_hoops_GIPGA[i++] = (NSOpenGLPixelFormatAttribute)2;
		else
			_hoops_GIPGA[i++] = (NSOpenGLPixelFormatAttribute)dc->options._hoops_AIPGA;
	}
	
	if (dc->options._hoops_PIPGA) {
		_hoops_GIPGA[i++] = NSOpenGLPFAStencilSize;
		_hoops_GIPGA[i++] = 8;
	}
	
	_hoops_GIPGA[i++] = NSOpenGLPFAAccumSize;
	_hoops_GIPGA[i++] = 32;	
	
	// _hoops_GHHR
	_hoops_GIPGA[i++] = 0;	
	
	NSOpenGLPixelFormat* _hoops_HIPGA = [[NSOpenGLPixelFormat alloc] initWithAttributes:_hoops_GIPGA];	
	
	// _hoops_SR _hoops_CPSA _hoops_RRP _hoops_IS _hoops_HPPR _hoops_HHH _hoops_IIPGA _hoops_AIR _hoops_AGHS _hoops_ARI _hoops_HIH _hoops_IH _hoops_HA _hoops_SAHR _hoops_CIPGA
	if(_hoops_HIPGA == nil) {		
		
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "Couldn't set pixel format");
		HD_Kill_Driver (dc);
		return;		
	}	
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		
		NSOpenGLContext *context = [[NSOpenGLContext alloc] initWithFormat: _hoops_HIPGA
															  shareContext: nil];
		
		_hoops_CSRGR->_hoops_SIPGA = context;
		_hoops_CSRGR->_hoops_GCPGA = 0;
	}
	
	else if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {
		
		NSOpenGLView *_hoops_IHPGA = _hoops_CSRGR->_hoops_IHPGA;
		
		[_hoops_IHPGA setPixelFormat:_hoops_HIPGA];
		
		_hoops_CSRGR->_hoops_SIPGA = [_hoops_IHPGA openGLContext];
		_hoops_CSRGR->_hoops_GCPGA = 0;
		
	}
	
	else if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) {
		
		NSView *_hoops_IHPGA = _hoops_CSRGR->_hoops_IHPGA;
		
		
		NSOpenGLContext *context = [[NSOpenGLContext alloc] initWithFormat: _hoops_HIPGA
															  shareContext: nil];
		[context setView:_hoops_IHPGA];
		
		
		_hoops_CSRGR->_hoops_SIPGA = context;
		_hoops_CSRGR->_hoops_GCPGA = 0;
	}
	
	{
		GLint backing_store = 0;
		[_hoops_HIPGA getValues : &backing_store forAttribute : NSOpenGLPFABackingStore forVirtualScreen : 0];
		
		if (backing_store)
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
		else
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;		
	}
	
	{
		GLint _hoops_PCPGA = 0;
		[_hoops_HIPGA getValues : &_hoops_PCPGA forAttribute : NSOpenGLPFAAccumSize forVirtualScreen : 0];
		_hoops_CSRGR->accumulation_bits = _hoops_PCPGA;
	}	
	
	[pool drain];	
	
	// _hoops_HAR _hoops_GPCPR _hoops_RCRR _hoops_RSH _hoops_RGR _hoops_CHH _hoops_IHPS...
	if (!_hoops_CSRGR->_hoops_SIPGA) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "no valid context at the end of choose_pixel_format");
		HD_Kill_Driver (dc);
		return;
	}	
}

local unsigned int ogl_bundle_users = 0;
local CFBundleRef ogl_bundle_ref = 0;

local void * GetFunctionPointerFromBundle(const char *name, CFBundleRef _hoops_HCPGA)
{
	void *function = 0;
	
	if (_hoops_HCPGA) {
		CFStringRef _hoops_ICPGA = CFStringCreateWithCString(CFAllocatorGetDefault(), name, kCFStringEncodingMacRoman);
		function = CFBundleGetFunctionPointerForName(_hoops_HCPGA, _hoops_ICPGA);
		CFRelease(_hoops_ICPGA);
	}
	return function;
}

local void * _hoops_CCPGA(const char *_hoops_SCPGA)
{
	
	if (!ogl_bundle_ref) {
		return 0;
	}
	
	return GetFunctionPointerFromBundle(_hoops_SCPGA, ogl_bundle_ref);	
}

local CFBundleRef LoadSystemFrameWorkBundle(const char *frameworkName)
{
	FSRef _hoops_GSPGA, _hoops_RSPGA;
	CFBundleRef _hoops_ASPGA = NULL;
	
	if (FSFindFolder(kSystemDomain, kFrameworksFolderType, false, &_hoops_GSPGA) == noErr) {
		
		HFSUniStr255 _hoops_PSPGA;
		CFStringRef _hoops_HSPGA;
		
		/* _hoops_CAAA _hoops_IHRPR _hoops_GSGR _hoops_IS _hoops_ISPGA [_hoops_CSPGA] _hoops_PIH _hoops_PPARR */
		_hoops_HSPGA = CFStringCreateWithCString(CFAllocatorGetDefault(), frameworkName, kCFStringEncodingMacRoman);
		_hoops_PSPGA.length = CFStringGetLength(_hoops_HSPGA);
		CFStringGetCharacters(_hoops_HSPGA, CFRangeMake(0,_hoops_PSPGA.length), _hoops_PSPGA.unicode);
		CFRelease(_hoops_HSPGA);
		
		if (FSMakeFSRefUnicode(&_hoops_GSPGA, _hoops_PSPGA.length, _hoops_PSPGA.unicode, CFStringGetSystemEncoding(), &_hoops_RSPGA) == noErr) {
			
			CFURLRef urlRef = CFURLCreateFromFSRef(CFAllocatorGetDefault(), &_hoops_RSPGA);
			
			if (urlRef) {
				_hoops_ASPGA=CFBundleCreate(CFAllocatorGetDefault(), urlRef);
				CFRelease(urlRef);
			}
		}
	}  
	/* _hoops_PCSA _hoops_IS _hoops_SSPGA _hoops_RGR _hoops_CGPR _hoops_RHAC _hoops_CHR _hoops_CPHR!! */
	return _hoops_ASPGA;	  
}


#endif
