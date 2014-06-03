#ifndef MYINPUT_H
#define MYINPUT_H
#include "math3d.h"

class Window;

class Input
{
public:
	enum
	{
		MOUSE_LEFT_BUTTON = 1,
		MOUSE_MIDDLE_BUTTON = 2,
		MOUSE_RIGHT_BUTTON = 3,
		MOUSE_WHEEL_UP = 4,
		MOUSE_WHEEL_DOWN = 5
	};

	enum
	{
			KEY_UNKNOWN = 0,

		/**
		 *  \name Usage page 0x07
		 *
		 *  These values are from usage page 0x07 (USB keyboard page).
		 */
		/*@{*/

		KEY_A = 4,
		KEY_B = 5,
		KEY_C = 6,
		KEY_D = 7,
		KEY_E = 8,
		KEY_F = 9,
		KEY_G = 10,
		KEY_H = 11,
		KEY_I = 12,
		KEY_J = 13,
		KEY_K = 14,
		KEY_L = 15,
		KEY_M = 16,
		KEY_N = 17,
		KEY_O = 18,
		KEY_P = 19,
		KEY_Q = 20,
		KEY_R = 21,
		KEY_S = 22,
		KEY_T = 23,
		KEY_U = 24,
		KEY_V = 25,
		KEY_W = 26,
		KEY_X = 27,
		KEY_Y = 28,
		KEY_Z = 29,

		KEY_1 = 30,
		KEY_2 = 31,
		KEY_3 = 32,
		KEY_4 = 33,
		KEY_5 = 34,
		KEY_6 = 35,
		KEY_7 = 36,
		KEY_8 = 37,
		KEY_9 = 38,
		KEY_0 = 39,

		KEY_RETURN = 40,
		KEY_ESCAPE = 41,
		KEY_BACKSPACE = 42,
		KEY_TAB = 43,
		KEY_SPACE = 44,

		KEY_MINUS = 45,
		KEY_EQUALS = 46,
		KEY_LEFTBRACKET = 47,
		KEY_RIGHTBRACKET = 48,
		KEY_BACKSLASH = 49, /**< Located at the lower left of the return
									  *   key on ISO keyboards and at the right end
									  *   of the QWERTY row on ANSI keyboards.
									  *   Produces REVERSE SOLIDUS (backslash) and
									  *   VERTICAL LINE in a US layout, REVERSE
									  *   SOLIDUS and VERTICAL LINE in a UK Mac
									  *   layout, NUMBER SIGN and TILDE in a UK
									  *   Windows layout, DOLLAR SIGN and POUND SIGN
									  *   in a Swiss German layout, NUMBER SIGN and
									  *   APOSTROPHE in a German layout, GRAVE
									  *   ACCENT and POUND SIGN in a French Mac
									  *   layout, and ASTERISK and MICRO SIGN in a
									  *   French Windows layout.
									  */
		KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
									  *   instead of 49 for the same key, but all
									  *   OSes I've seen treat the two codes
									  *   identically. So, as an implementor, unless
									  *   your keyboard generates both of those
									  *   codes and your OS treats them differently,
									  *   you should generate KEY_BACKSLASH
									  *   instead of this code. As a user, you
									  *   should not rely on this code because SDL
									  *   will never generate it with most (all?)
									  *   keyboards.
									  */
		KEY_SEMICOLON = 51,
		KEY_APOSTROPHE = 52,
		KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
								  *   and ISO keyboards). Produces GRAVE ACCENT and
								  *   TILDE in a US Windows layout and in US and UK
								  *   Mac layouts on ANSI keyboards, GRAVE ACCENT
								  *   and NOT SIGN in a UK Windows layout, SECTION
								  *   SIGN and PLUS-MINUS SIGN in US and UK Mac
								  *   layouts on ISO keyboards, SECTION SIGN and
								  *   DEGREE SIGN in a Swiss German layout (Mac:
								  *   only on ISO keyboards), CIRCUMFLEX ACCENT and
								  *   DEGREE SIGN in a German layout (Mac: only on
								  *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
								  *   French Windows layout, COMMERCIAL AT and
								  *   NUMBER SIGN in a French Mac layout on ISO
								  *   keyboards, and LESS-THAN SIGN and GREATER-THAN
								  *   SIGN in a Swiss German, German, or French Mac
								  *   layout on ANSI keyboards.
								  */
		KEY_COMMA = 54,
		KEY_PERIOD = 55,
		KEY_SLASH = 56,

		KEY_CAPSLOCK = 57,

		KEY_F1 = 58,
		KEY_F2 = 59,
		KEY_F3 = 60,
		KEY_F4 = 61,
		KEY_F5 = 62,
		KEY_F6 = 63,
		KEY_F7 = 64,
		KEY_F8 = 65,
		KEY_F9 = 66,
		KEY_F10 = 67,
		KEY_F11 = 68,
		KEY_F12 = 69,

		KEY_PRINTSCREEN = 70,
		KEY_SCROLLLOCK = 71,
		KEY_PAUSE = 72,
		KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
									   does send code 73, not 117) */
		KEY_HOME = 74,
		KEY_PAGEUP = 75,
		KEY_DELETE = 76,
		KEY_END = 77,
		KEY_PAGEDOWN = 78,
		KEY_RIGHT = 79,
		KEY_LEFT = 80,
		KEY_DOWN = 81,
		KEY_UP = 82,

		KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
										 */
		KEY_KP_DIVIDE = 84,
		KEY_KP_MULTIPLY = 85,
		KEY_KP_MINUS = 86,
		KEY_KP_PLUS = 87,
		KEY_KP_ENTER = 88,
		KEY_KP_1 = 89,
		KEY_KP_2 = 90,
		KEY_KP_3 = 91,
		KEY_KP_4 = 92,
		KEY_KP_5 = 93,
		KEY_KP_6 = 94,
		KEY_KP_7 = 95,
		KEY_KP_8 = 96,
		KEY_KP_9 = 97,
		KEY_KP_0 = 98,
		KEY_KP_PERIOD = 99,

		KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
											*   keyboards have over ANSI ones,
											*   located between left shift and Y.
											*   Produces GRAVE ACCENT and TILDE in a
											*   US or UK Mac layout, REVERSE SOLIDUS
											*   (backslash) and VERTICAL LINE in a
											*   US or UK Windows layout, and
											*   LESS-THAN SIGN and GREATER-THAN SIGN
											*   in a Swiss German, German, or French
											*   layout. */
		KEY_APPLICATION = 101, /**< windows contextual menu, compose */
		KEY_POWER = 102, /**< The USB document says this is a status flag,
								   *   not a physical key - but some Mac keyboards
								   *   do have a power key. */
		KEY_KP_EQUALS = 103,
		KEY_F13 = 104,
		KEY_F14 = 105,
		KEY_F15 = 106,
		KEY_F16 = 107,
		KEY_F17 = 108,
		KEY_F18 = 109,
		KEY_F19 = 110,
		KEY_F20 = 111,
		KEY_F21 = 112,
		KEY_F22 = 113,
		KEY_F23 = 114,
		KEY_F24 = 115,
		KEY_EXECUTE = 116,
		KEY_HELP = 117,
		KEY_MENU = 118,
		KEY_SELECT = 119,
		KEY_STOP = 120,
		KEY_AGAIN = 121,   /**< redo */
		KEY_UNDO = 122,
		KEY_CUT = 123,
		KEY_COPY = 124,
		KEY_PASTE = 125,
		KEY_FIND = 126,
		KEY_MUTE = 127,
		KEY_VOLUMEUP = 128,
		KEY_VOLUMEDOWN = 129,
	/* not sure whether there's a reason to enable these */
	/*     KEY_LOCKINGCAPSLOCK = 130,  */
	/*     KEY_LOCKINGNUMLOCK = 131, */
	/*     KEY_LOCKINGSCROLLLOCK = 132, */
		KEY_KP_COMMA = 133,
		KEY_KP_EQUALSAS400 = 134,

		KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
												footnotes in USB doc */
		KEY_INTERNATIONAL2 = 136,
		KEY_INTERNATIONAL3 = 137, /**< Yen */
		KEY_INTERNATIONAL4 = 138,
		KEY_INTERNATIONAL5 = 139,
		KEY_INTERNATIONAL6 = 140,
		KEY_INTERNATIONAL7 = 141,
		KEY_INTERNATIONAL8 = 142,
		KEY_INTERNATIONAL9 = 143,
		KEY_LANG1 = 144, /**< Hangul/English toggle */
		KEY_LANG2 = 145, /**< Hanja conversion */
		KEY_LANG3 = 146, /**< Katakana */
		KEY_LANG4 = 147, /**< Hiragana */
		KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
		KEY_LANG6 = 149, /**< reserved */
		KEY_LANG7 = 150, /**< reserved */
		KEY_LANG8 = 151, /**< reserved */
		KEY_LANG9 = 152, /**< reserved */

		KEY_ALTERASE = 153, /**< Erase-Eaze */
		KEY_SYSREQ = 154,
		KEY_CANCEL = 155,
		KEY_CLEAR = 156,
		KEY_PRIOR = 157,
		KEY_RETURN2 = 158,
		KEY_SEPARATOR = 159,
		KEY_OUT = 160,
		KEY_OPER = 161,
		KEY_CLEARAGAIN = 162,
		KEY_CRSEL = 163,
		KEY_EXSEL = 164,

		KEY_KP_00 = 176,
		KEY_KP_000 = 177,
		KEY_THOUSANDSSEPARATOR = 178,
		KEY_DECIMALSEPARATOR = 179,
		KEY_CURRENCYUNIT = 180,
		KEY_CURRENCYSUBUNIT = 181,
		KEY_KP_LEFTPAREN = 182,
		KEY_KP_RIGHTPAREN = 183,
		KEY_KP_LEFTBRACE = 184,
		KEY_KP_RIGHTBRACE = 185,
		KEY_KP_TAB = 186,
		KEY_KP_BACKSPACE = 187,
		KEY_KP_A = 188,
		KEY_KP_B = 189,
		KEY_KP_C = 190,
		KEY_KP_D = 191,
		KEY_KP_E = 192,
		KEY_KP_F = 193,
		KEY_KP_XOR = 194,
		KEY_KP_POWER = 195,
		KEY_KP_PERCENT = 196,
		KEY_KP_LESS = 197,
		KEY_KP_GREATER = 198,
		KEY_KP_AMPERSAND = 199,
		KEY_KP_DBLAMPERSAND = 200,
		KEY_KP_VERTICALBAR = 201,
		KEY_KP_DBLVERTICALBAR = 202,
		KEY_KP_COLON = 203,
		KEY_KP_HASH = 204,
		KEY_KP_SPACE = 205,
		KEY_KP_AT = 206,
		KEY_KP_EXCLAM = 207,
		KEY_KP_MEMSTORE = 208,
		KEY_KP_MEMRECALL = 209,
		KEY_KP_MEMCLEAR = 210,
		KEY_KP_MEMADD = 211,
		KEY_KP_MEMSUBTRACT = 212,
		KEY_KP_MEMMULTIPLY = 213,
		KEY_KP_MEMDIVIDE = 214,
		KEY_KP_PLUSMINUS = 215,
		KEY_KP_CLEAR = 216,
		KEY_KP_CLEARENTRY = 217,
		KEY_KP_BINARY = 218,
		KEY_KP_OCTAL = 219,
		KEY_KP_DECIMAL = 220,
		KEY_KP_HEXADECIMAL = 221,

		KEY_LCTRL = 224,
		KEY_LSHIFT = 225,
		KEY_LALT = 226, /**< alt, option */
		KEY_LGUI = 227, /**< windows, command (apple), meta */
		KEY_RCTRL = 228,
		KEY_RSHIFT = 229,
		KEY_RALT = 230, /**< alt gr, option */
		KEY_RGUI = 231, /**< windows, command (apple), meta */

		KEY_MODE = 257,    /**< I'm not sure if this is really not covered
									 *   by any of the above, but since there's a
									 *   special KMOD_MODE for it I'm adding it here
									 */

		/*@}*//*Usage page 0x07*/

		/**
		 *  \name Usage page 0x0C
		 *
		 *  These values are mapped from usage page 0x0C (USB consumer page).
		 */
		/*@{*/

		KEY_AUDIONEXT = 258,
		KEY_AUDIOPREV = 259,
		KEY_AUDIOSTOP = 260,
		KEY_AUDIOPLAY = 261,
		KEY_AUDIOMUTE = 262,
		KEY_MEDIASELECT = 263,
		KEY_WWW = 264,
		KEY_MAIL = 265,
		KEY_CALCULATOR = 266,
		KEY_COMPUTER = 267,
		KEY_AC_SEARCH = 268,
		KEY_AC_HOME = 269,
		KEY_AC_BACK = 270,
		KEY_AC_FORWARD = 271,
		KEY_AC_STOP = 272,
		KEY_AC_REFRESH = 273,
		KEY_AC_BOOKMARKS = 274,

		/*@}*//*Usage page 0x0C*/

		/**
		 *  \name Walther keys
		 *
		 *  These are values that Christian Walther added (for mac keyboard?).
		 */
		/*@{*/

		KEY_BRIGHTNESSDOWN = 275,
		KEY_BRIGHTNESSUP = 276,
		KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
											   switch, video mode switch */
		KEY_KBDILLUMTOGGLE = 278,
		KEY_KBDILLUMDOWN = 279,
		KEY_KBDILLUMUP = 280,
		KEY_EJECT = 281,
		KEY_SLEEP = 282,

		KEY_APP1 = 283,
		KEY_APP2 = 284,
	};

	//typedef enum {
	//        /** @name ASCII mapped keysyms
	//         *  The keyboard syms have been cleverly chosen to map to ASCII
	//         */
	//        /*@{*/
	//	KEY_UNKNOWN		= 0,
	//	KEY_FIRST		= 0,
	//	KEY_BACKSPACE		= 8,
	//	KEY_TAB		= 9,
	//	KEY_CLEAR		= 12,
	//	KEY_RETURN		= 13,
	//	KEY_PAUSE		= 19,
	//	KEY_ESCAPE		= 27,
	//	KEY_SPACE		= 32,
	//	KEY_EXCLAIM		= 33,
	//	KEY_QUOTEDBL		= 34,
	//	KEY_HASH		= 35,
	//	KEY_DOLLAR		= 36,
	//	KEY_AMPERSAND		= 38,
	//	KEY_QUOTE		= 39,
	//	KEY_LEFTPAREN		= 40,
	//	KEY_RIGHTPAREN		= 41,
	//	KEY_ASTERISK		= 42,
	//	KEY_PLUS		= 43,
	//	KEY_COMMA		= 44,
	//	KEY_MINUS		= 45,
	//	KEY_PERIOD		= 46,
	//	KEY_SLASH		= 47,
	//	KEY_0			= 48,
	//	KEY_1			= 49,
	//	KEY_2			= 50,
	//	KEY_3			= 51,
	//	KEY_4			= 52,
	//	KEY_5			= 53,
	//	KEY_6			= 54,
	//	KEY_7			= 55,
	//	KEY_8			= 56,
	//	KEY_9			= 57,
	//	KEY_COLON		= 58,
	//	KEY_SEMICOLON		= 59,
	//	KEY_LESS		= 60,
	//	KEY_EQUALS		= 61,
	//	KEY_GREATER		= 62,
	//	KEY_QUESTION		= 63,
	//	KEY_AT			= 64,
	//	/* 
	//	   Skip uppercase letters
	//	 */
	//	KEY_LEFTBRACKET	= 91,
	//	KEY_BACKSLASH		= 92,
	//	KEY_RIGHTBRACKET	= 93,
	//	KEY_CARET		= 94,
	//	KEY_UNDERSCORE		= 95,
	//	KEY_BACKQUOTE		= 96,
	//	KEY_a			= 97,
	//	KEY_b			= 98,
	//	KEY_c			= 99,
	//	KEY_d			= 100,
	//	KEY_e			= 101,
	//	KEY_f			= 102,
	//	KEY_g			= 103,
	//	KEY_h			= 104,
	//	KEY_i			= 105,
	//	KEY_j			= 106,
	//	KEY_k			= 107,
	//	KEY_l			= 108,
	//	KEY_m			= 109,
	//	KEY_n			= 110,
	//	KEY_o			= 111,
	//	KEY_p			= 112,
	//	KEY_q			= 113,
	//	KEY_r			= 114,
	//	KEY_s			= 115,
	//	KEY_t			= 116,
	//	KEY_u			= 117,
	//	KEY_v			= 118,
	//	KEY_w			= 119,
	//	KEY_x			= 120,
	//	KEY_y			= 121,
	//	KEY_z			= 122,
	//	KEY_DELETE		= 127,
	//	/* End of ASCII mapped keysyms */
	//        /*@}*/
	//
	//	/** @name International keyboard syms */
	//        /*@{*/
	//	KEY_WORLD_0		= 160,		/* 0xA0 */
	//	KEY_WORLD_1		= 161,
	//	KEY_WORLD_2		= 162,
	//	KEY_WORLD_3		= 163,
	//	KEY_WORLD_4		= 164,
	//	KEY_WORLD_5		= 165,
	//	KEY_WORLD_6		= 166,
	//	KEY_WORLD_7		= 167,
	//	KEY_WORLD_8		= 168,
	//	KEY_WORLD_9		= 169,
	//	KEY_WORLD_10		= 170,
	//	KEY_WORLD_11		= 171,
	//	KEY_WORLD_12		= 172,
	//	KEY_WORLD_13		= 173,
	//	KEY_WORLD_14		= 174,
	//	KEY_WORLD_15		= 175,
	//	KEY_WORLD_16		= 176,
	//	KEY_WORLD_17		= 177,
	//	KEY_WORLD_18		= 178,
	//	KEY_WORLD_19		= 179,
	//	KEY_WORLD_20		= 180,
	//	KEY_WORLD_21		= 181,
	//	KEY_WORLD_22		= 182,
	//	KEY_WORLD_23		= 183,
	//	KEY_WORLD_24		= 184,
	//	KEY_WORLD_25		= 185,
	//	KEY_WORLD_26		= 186,
	//	KEY_WORLD_27		= 187,
	//	KEY_WORLD_28		= 188,
	//	KEY_WORLD_29		= 189,
	//	KEY_WORLD_30		= 190,
	//	KEY_WORLD_31		= 191,
	//	KEY_WORLD_32		= 192,
	//	KEY_WORLD_33		= 193,
	//	KEY_WORLD_34		= 194,
	//	KEY_WORLD_35		= 195,
	//	KEY_WORLD_36		= 196,
	//	KEY_WORLD_37		= 197,
	//	KEY_WORLD_38		= 198,
	//	KEY_WORLD_39		= 199,
	//	KEY_WORLD_40		= 200,
	//	KEY_WORLD_41		= 201,
	//	KEY_WORLD_42		= 202,
	//	KEY_WORLD_43		= 203,
	//	KEY_WORLD_44		= 204,
	//	KEY_WORLD_45		= 205,
	//	KEY_WORLD_46		= 206,
	//	KEY_WORLD_47		= 207,
	//	KEY_WORLD_48		= 208,
	//	KEY_WORLD_49		= 209,
	//	KEY_WORLD_50		= 210,
	//	KEY_WORLD_51		= 211,
	//	KEY_WORLD_52		= 212,
	//	KEY_WORLD_53		= 213,
	//	KEY_WORLD_54		= 214,
	//	KEY_WORLD_55		= 215,
	//	KEY_WORLD_56		= 216,
	//	KEY_WORLD_57		= 217,
	//	KEY_WORLD_58		= 218,
	//	KEY_WORLD_59		= 219,
	//	KEY_WORLD_60		= 220,
	//	KEY_WORLD_61		= 221,
	//	KEY_WORLD_62		= 222,
	//	KEY_WORLD_63		= 223,
	//	KEY_WORLD_64		= 224,
	//	KEY_WORLD_65		= 225,
	//	KEY_WORLD_66		= 226,
	//	KEY_WORLD_67		= 227,
	//	KEY_WORLD_68		= 228,
	//	KEY_WORLD_69		= 229,
	//	KEY_WORLD_70		= 230,
	//	KEY_WORLD_71		= 231,
	//	KEY_WORLD_72		= 232,
	//	KEY_WORLD_73		= 233,
	//	KEY_WORLD_74		= 234,
	//	KEY_WORLD_75		= 235,
	//	KEY_WORLD_76		= 236,
	//	KEY_WORLD_77		= 237,
	//	KEY_WORLD_78		= 238,
	//	KEY_WORLD_79		= 239,
	//	KEY_WORLD_80		= 240,
	//	KEY_WORLD_81		= 241,
	//	KEY_WORLD_82		= 242,
	//	KEY_WORLD_83		= 243,
	//	KEY_WORLD_84		= 244,
	//	KEY_WORLD_85		= 245,
	//	KEY_WORLD_86		= 246,
	//	KEY_WORLD_87		= 247,
	//	KEY_WORLD_88		= 248,
	//	KEY_WORLD_89		= 249,
	//	KEY_WORLD_90		= 250,
	//	KEY_WORLD_91		= 251,
	//	KEY_WORLD_92		= 252,
	//	KEY_WORLD_93		= 253,
	//	KEY_WORLD_94		= 254,
	//	KEY_WORLD_95		= 255,		/* 0xFF */
	//        /*@}*/
	//
	//	/** @name Numeric keypad */
	//        /*@{*/
	//	KEY_KP0		= 256,
	//	KEY_KP1		= 257,
	//	KEY_KP2		= 258,
	//	KEY_KP3		= 259,
	//	KEY_KP4		= 260,
	//	KEY_KP5		= 261,
	//	KEY_KP6		= 262,
	//	KEY_KP7		= 263,
	//	KEY_KP8		= 264,
	//	KEY_KP9		= 265,
	//	KEY_KP_PERIOD		= 266,
	//	KEY_KP_DIVIDE		= 267,
	//	KEY_KP_MULTIPLY	= 268,
	//	KEY_KP_MINUS		= 269,
	//	KEY_KP_PLUS		= 270,
	//	KEY_KP_ENTER		= 271,
	//	KEY_KP_EQUALS		= 272,
	//        /*@}*/
	//
	//	/** @name Arrows + Home/End pad */
	//        /*@{*/
	//	KEY_UP			= 273,
	//	KEY_DOWN		= 274,
	//	KEY_RIGHT		= 275,
	//	KEY_LEFT		= 276,
	//	KEY_INSERT		= 277,
	//	KEY_HOME		= 278,
	//	KEY_END		= 279,
	//	KEY_PAGEUP		= 280,
	//	KEY_PAGEDOWN		= 281,
	//        /*@}*/
	//
	//	/** @name Function keys */
	//        /*@{*/
	//	KEY_F1			= 282,
	//	KEY_F2			= 283,
	//	KEY_F3			= 284,
	//	KEY_F4			= 285,
	//	KEY_F5			= 286,
	//	KEY_F6			= 287,
	//	KEY_F7			= 288,
	//	KEY_F8			= 289,
	//	KEY_F9			= 290,
	//	KEY_F10		= 291,
	//	KEY_F11		= 292,
	//	KEY_F12		= 293,
	//	KEY_F13		= 294,
	//	KEY_F14		= 295,
	//	KEY_F15		= 296,
	//        /*@}*/
	//
	//	/** @name Key state modifier keys */
	//        /*@{*/
	//	KEY_NUMLOCK		= 300,
	//	KEY_CAPSLOCK		= 301,
	//	KEY_SCROLLOCK		= 302,
	//	KEY_RSHIFT		= 303,
	//	KEY_LSHIFT		= 304,
	//	KEY_RCTRL		= 305,
	//	KEY_LCTRL		= 306,
	//	KEY_RALT		= 307,
	//	KEY_LALT		= 308,
	//	KEY_RMETA		= 309,
	//	KEY_LMETA		= 310,
	//	KEY_LSUPER		= 311,		/**< Left "Windows" key */
	//	KEY_RSUPER		= 312,		/**< Right "Windows" key */
	//	KEY_MODE		= 313,		/**< "Alt Gr" key */
	//	KEY_COMPOSE		= 314,		/**< Multi-key compose key */
	//        /*@}*/
	//
	//	/** @name Miscellaneous function keys */
	//        /*@{*/
	//	KEY_HELP		= 315,
	//	KEY_PRINT		= 316,
	//	KEY_SYSREQ		= 317,
	//	KEY_BREAK		= 318,
	//	KEY_MENU		= 319,
	//	KEY_POWER		= 320,		/**< Power Macintosh power key */
	//	KEY_EURO		= 321,		/**< Some european keyboards */
	//	KEY_UNDO		= 322,		/**< Atari keyboard has Undo */
	//        /*@}*/
	//
	//	/* Add any other keys here */
	//
	//	KEY_LAST
	//} KEY;

	static const int NUM_KEYS = 512;
	static const int NUM_MOUSEBUTTONS = 256;

	Input(Window* window);

	inline bool GetKey(int keyCode)            const { return m_inputs[keyCode]; }
	inline bool GetKeyDown(int keyCode)        const { return m_downKeys[keyCode]; }
	inline bool GetKeyUp(int keyCode)          const { return m_upKeys[keyCode]; }
	inline bool GetMouse(int keyCode)          const { return m_mouseInput[keyCode]; }
	inline bool GetMouseDown(int keyCode)      const { return m_downMouse[keyCode]; }
	inline bool GetMouseUp(int keyCode)        const { return m_upMouse[keyCode]; }
	inline Vector2f GetMousePosition()         const { return Vector2f((float)m_mouseX, (float)m_mouseY); }
	
	void SetCursor(bool value)                 const;
	void SetMousePosition(const Vector2f& pos) const;
	
	inline void SetKey(int keyCode, bool value)       { m_inputs[keyCode] = value; }
	inline void SetKeyDown(int keyCode, bool value)   { m_downKeys[keyCode] = value; }
	inline void SetKeyUp(int keyCode, bool value)     { m_upKeys[keyCode] = value; }
	inline void SetMouse(int keyCode, bool value)     { m_mouseInput[keyCode] = value; }
	inline void SetMouseDown(int keyCode, bool value) { m_downMouse[keyCode] = value; }
	inline void SetMouseUp(int keyCode, bool value)   { m_upMouse[keyCode] = value; }
	inline void SetMouseX(int value)                  { m_mouseX = value; }
	inline void SetMouseY(int value)                  { m_mouseY = value; }
protected:
private:
	bool m_inputs[NUM_KEYS];
	bool m_downKeys[NUM_KEYS];
	bool m_upKeys[NUM_KEYS];
	bool m_mouseInput[NUM_MOUSEBUTTONS];
	bool m_downMouse[NUM_MOUSEBUTTONS];
	bool m_upMouse[NUM_MOUSEBUTTONS];
	int  m_mouseX;
	int  m_mouseY;
	Window* m_window;
};

#endif
