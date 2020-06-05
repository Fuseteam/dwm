/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int snap      = 32;       /* snap pixel */
static const double inactiveopacity = 0.80;
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

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, ALPHA,  OPAQUE},
	[SchemeSel]  = { OPAQUE, ALPHA,  OPAQUE},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor opacity inactiveopacity*/
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,     -1,     -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1,     0.95,   1.0 },
};

static const MonitorRule monrules[] = {
	/* monitor layout  mfact  nmaster  showbar  topbar  borderpx  defaultopacity */
	{  1,      0,      0.50,    -1,      1,      1,     1,         0.95     }, // use a different layout for the second monitor
	{  -1,     0,      0.55,    1,      1,      1,     1,         0.95     }, // default
};

/* layout(s) */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY  Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress,    MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress,    MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress,    MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress,    MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *lanu[] = { "dibus", NULL };

/* custom functions */
static const char emoji[130]="[ `ibus engine` = uniemoji ] && ibus engine `cat .local/dwm/ibus` || `ibus engine > .local/dwm/ibus && ibus engine uniemoji`";
static const char *toggleemoji[] = { "/bin/sh", "-c",emoji, NULL };
static const char *scrot[] = { "/bin/sh", "-c", "cd `cat .config/dwm/scrotdir`;scrot", NULL };
static const char *scrots[] = { "/bin/sh", "-c", "cd `cat .config/dwm/scrotdir`;scrot -s", NULL };
static const char *scrotu[] = { "/bin/sh", "-c", "cd `cat .config/dwm/scrotdir`;scrot -u", NULL };
static const char *voldec[] = { "/bin/sh", "-c", "pactl -- set-sink-volume 0 -10%", NULL };
static const char *volinc[] = { "/bin/sh", "-c", "pactl -- set-sink-volume 0 +10%", NULL };
static const char *volmut[] = { "/bin/sh", "-c", "amixer -D pulse set Master toggle", NULL };

static Key keys[] = {
	/*  type       modifier                         key          function        argument */
	{ KeyPress,    MODKEY,                          XK_r,        spawn,          {.v = dmenucmd } },
	{ KeyPress,    MODKEY|ShiftMask,                XK_r,	     spawn,          {.v = termcmd } },
	{ KeyPress,    MODKEY,                          XK_e,        spawn,          {.v = toggleemoji } },
	{ KeyPress,    MODKEY,                          XK_l,        spawn,          {.v = lanu } },
	{ KeyPress,    MODKEY|ShiftMask,                XK_Return,   spawn,          {.v = browser } },
	{ KeyPress,    0,                               XK_Print,    spawn,          {.v = scrot } },
	{ KeyRelease,  ShiftMask,                       XK_Print,    spawn,          {.v = scrots } },
	{ KeyRelease,  ControlMask,                     XK_Print,    spawn,          {.v = scrotu } },
	{ KeyPress,    MODKEY|ControlMask,              XK_d,        spawn,	     {.v = voldec} },
	{ KeyPress,    MODKEY|ControlMask,              XK_i,        spawn,	     {.v = volinc} },
	{ KeyPress,    MODKEY|ControlMask,              XK_m,        spawn,	     {.v = volmut} },
	{ KeyPress,    MODKEY|ShiftMask,                XK_d,        setopacity,     {.f = -0.05} },
	{ KeyPress,    MODKEY|ShiftMask,                XK_i,        setopacity,     {.f = +0.05} },
	{ KeyPress,    MODKEY|ShiftMask,                XK_f,        setopacity,     {.f = 2.0} },
	{ KeyPress,    MODKEY,                          XK_b,        togglebar,      {0} },
	{ KeyPress,    AltMask,                         XK_Tab,      focusstack,     {.i = +1 } },
	{ KeyPress,    AltMask|ShiftMask,               XK_Tab,      focusstack,     {.i = -1 } },
	{ KeyPress,    MODKEY,                          XK_i,        incnmaster,     {.i = +1 } },
	{ KeyPress,    MODKEY,                          XK_d,        incnmaster,     {.i = -1 } },
	{ KeyPress,    MODKEY,                          XK_h,        setmfact,       {.f = -0.05} },
	{ KeyPress,    MODKEY,                          XK_l,        setmfact,       {.f = +0.05} },
	{ KeyPress,    MODKEY,                          XK_Return,   zoom,           {0} },
	{ KeyPress,    MODKEY,                          XK_Tab,      view,           {0} },
	{ KeyPress,    MODKEY|ShiftMask,                XK_c,        killclient,     {0} },
	{ KeyPress,    MODKEY,                          XK_t,        setlayout,      {.v = &layouts[0]} },
	{ KeyPress,    MODKEY,                          XK_f,        setlayout,      {.v = &layouts[1]} },
	{ KeyPress,    MODKEY,                          XK_m,        setlayout,      {.v = &layouts[2]} },
	{ KeyPress,    MODKEY,                          XK_space,    setlayout,      {0} },
	{ KeyPress,    MODKEY|ShiftMask,                XK_space,    togglefloating, {0} },
	{ KeyPress,    MODKEY,                          XK_0,        view,           {.ui = ~0 } },
	{ KeyPress,    MODKEY|ShiftMask,                XK_0,        tag,            {.ui = ~0 } },
	{ KeyPress,    MODKEY,                          XK_comma,    focusmon,       {.i = -1 } },
	{ KeyPress,    MODKEY,                          XK_period,   focusmon,       {.i = +1 } },
	{ KeyPress,    MODKEY|ShiftMask,                XK_comma,    tagmon,         {.i = -1 } },
	{ KeyPress,    MODKEY|ShiftMask,                XK_period,   tagmon,         {.i = +1 } },
	{ KeyPress,    MODKEY|ShiftMask|ControlMask,    XK_d,        setborderpx,    {.i = -1 } },
	{ KeyPress,    MODKEY|ShiftMask|ControlMask,    XK_i,        setborderpx,    {.i = +1 } },
	{ KeyPress,    MODKEY|ShiftMask|ControlMask,    XK_f,        setborderpx,    {.i = 0 } },
	{ KeyPress,    MODKEY|ShiftMask|ControlMask,    XK_m,        setborderpx,    {.i = 2 } },
	TAGKEYS(                                        XK_1,                        0)
	TAGKEYS(                                        XK_2,                        1)
	TAGKEYS(                                        XK_3,                        2)
	TAGKEYS(                                        XK_4,                        3)
	TAGKEYS(                                        XK_5,                        4)
	TAGKEYS(                                        XK_6,                        5)
	TAGKEYS(                                        XK_7,                        6)
	TAGKEYS(                                        XK_8,                        7)
	TAGKEYS(                                        XK_9,                        8)
	{ KeyPress,    MODKEY|ShiftMask,                XK_q,        quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask                button          function        argument */
	{ ClkLtSymbol,          0,                        Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                        Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                        Button2,        zoom,           {0} },
	{ ClkWinTitle,          0,                        Button3,        spawn,          {.v = volinc} },
	{ ClkWinTitle,          0,                        Button2,        spawn,          {.v = volmut} },
	{ ClkWinTitle,          0,                        Button1,        spawn,          {.v = voldec} },
	{ ClkStatusText,        0,                        Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,                   Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,                   Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,                   Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,         Button3,        setopacity,     {.f = 1.0} },
	{ ClkTagBar,            0,                        Button1,        view,           {0} },
	{ ClkTagBar,            0,                        Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,                   Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,                   Button3,        toggletag,      {0} },
};
