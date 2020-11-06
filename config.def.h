/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };    /* 定义alacritty终端的快捷建功能 */
static const char *volup[] = { "amixer", "-qM", "set", "Master", "2%+", "umute", NULL };
static const char *voldown[] = { "amixer", "-qM", "set", "Master", "2%-", "umute", NULL };   // 定义系统音量大小调节的快捷键功能
static const char *lightup[] = { "xbacklight", "-inc", "2", NULL };
static const char *lightdown[] = { "xbacklight", "-dec", "2", NULL };   //   定义屏幕亮度调节的快捷键功能
static const char *chromium[]  = { "chromium", "--disk-cache-dir=/tmp/chromium", NULL };   //   定义chromium浏览器的快捷键功能
static const char *dolphin[]  = { "dolphin", NULL };   //  定义dolphin文件管理器的快捷键功能

// XK_ 是指Alt键
static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY|ShiftMask,             XK_Up,     spawn,          {.v = lightup} },
        { MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = lightdown} },   // Shift+Alt+上/下方向键，调整屏幕亮度
        { MODKEY|ShiftMask,             XK_Right,  spawn,          {.v = volup} },
        { MODKEY|ShiftMask,             XK_Left,   spawn,          {.v = voldown} },     // Shift+Alt+左/右方向键，调整音量大小
        { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mute} },        // Shift+Alt+m，开启/关闭静音
        { MODKEY,                       XK_d,      spawn,          {.v = dolphin } },    // Alt+d，呼出dolphin文件管理器
        { MODKEY,                       XK_j,      spawn,          {.v = chromium } },   // Alt+j，呼出chromium浏览器
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },   // Alt+p，呼出dmenu应用程序启动器
        { MODKEY,                       XK_k,      spawn,          {.v = termcmd } },    // Alt+k，呼出alacritty终端
        { MODKEY,                       XK_Up,     focusstack,     {.i = +1 } },
        { MODKEY,                       XK_Down,   focusstack,     {.i = -1 } },         // Alt+上/下方向键，切换focus到不同的程序窗口
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },         // Alt+i/u，改变窗口布局
        { MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },       // Alt+左/右方向键，调整程序窗口的大小
        { MODKEY,                       XK_Return, zoom,           {0} },                // Alt+Enter键，将当前所在focus的窗口提升为主窗口(左边那个占比最大的窗口就是“主窗口”)
        { MODKEY|ControlMask,           XK_q,      killclient,     {0} },   // Ctrl+Alt+q，关闭并退出将当前所在focus的窗口程序
        { MODKEY|ControlMask,           XK_Delete,    quit,        {0} },   // Ctrl+Alt+del，关闭并退出整个dwm桌面，且强制关闭所有当前运行于dwm下的程序
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)   //  Alt+1/2/3/4/5/6/7/8/9，切换到不同的dwm顶部菜单栏的标签里
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

