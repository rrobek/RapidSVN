AC_INIT(rapidsvn, 0.13.0)
AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE(silent-rules subdir-objects)

AC_PROG_CXX
AC_PROG_INSTALL
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL

abs_srcdir="`cd $srcdir && pwd`"
SVNCPP_DIR="$abs_srcdir/libsvncpp"
LIBRAPIDSVN_DIR="$abs_srcdir/librapidsvn"
CPPFLAGS="$CPPFLAGS -I$SVNCPP_DIR/include"

dnl
dnl GCC specifics
dnl
AC_MSG_CHECKING([for gcc/g++])
if test "$GXX" = "yes" ; then
   AC_MSG_RESULT([found (using "-Wall", "-Wextra" and "-fexceptions")])
   CPPFLAGS="$CPPFLAGS -Wall -W -fexceptions"
   CXXFLAGS="$CXXFLAGS -Wall -W -fexceptions"
else
   AC_MSG_RESULT([non gcc/g++ compiler])
fi



dnl
dnl APR
dnl

APR_CONFIGS="apr-config apr-1-config /usr/local/apr/bin/apr-config"
AC_ARG_WITH(apr-config,
[[  --with-apr-config=FILE    Use the given path to apr-config when determining
                            APR configuration; defaults to "apr-config"]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        APR_CONFIGS=$withval
    fi
])
AC_MSG_CHECKING([for APR])
APR_CONFIG=""
for VALUE in $APR_CONFIGS ; do
  if $VALUE --cflags >/dev/null 2>&1; then
    APR_CONFIG=$VALUE
    break
  fi
done
if test $APR_CONFIG ; then
    AC_MSG_RESULT([found])
else
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([APR is required. Try --with-apr-config.])
fi

CPPFLAGS="$CPPFLAGS  `$APR_CONFIG --cppflags` `$APR_CONFIG --includes`"
APR_LIBS="`$APR_CONFIG --link-ld --libs`"

dnl
dnl APR util
dnl

APU_CONFIGS="apu-config apu-1-config /usr/local/apr/bin/apu-config"
AC_ARG_WITH(apu-config,
[[  --with-apu-config=FILE    Use the given path to apu-config when determining
                            APR util configuration; defaults to "apu-config"]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        APU_CONFIGS=$withval
    fi
])
AC_MSG_CHECKING([for APR util])
APU_CONFIG=""
for VALUE in $APU_CONFIGS ; do
  if $VALUE --includes >/dev/null 2>&1; then
    APU_CONFIG=$VALUE
    break
  fi
done
if test $APU_CONFIG ; then
    AC_MSG_RESULT([found])
else
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([APU util is required. Try --with-apu-config.])
fi
CPPFLAGS="$CPPFLAGS `$APU_CONFIG --includes`"
APR_LIBS="$APR_LIBS `$APU_CONFIG --link-ld --libs`"


dnl
dnl Subversion
dnl

SVN_INCLUDES="/usr/local/include /usr/include"
AC_ARG_WITH(svn-include,
[[  --with-svn-include=DIR   Use the given path to the subversion headers.]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        SVN_INCLUDES=$withval
    fi
])
AC_MSG_CHECKING([for Subversion headers])
SVN_INCLUDE=""
for VALUE in $SVN_INCLUDES ; do
    if test -f $VALUE/subversion-1/svn_types.h ; then
        SVN_INCLUDE=$VALUE
        break
    fi
done
if test $SVN_INCLUDE ; then
    AC_MSG_RESULT([found])
else
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Subversion headers are required. Try --with-svn-include.])
fi
CPPFLAGS="$CPPFLAGS -I$SVN_INCLUDE/subversion-1"

SVN_LIBS="/usr/lib64 /usr/local/lib /usr/lib /usr/lib/x86_64-linux-gnu /usr/lib/arm-linux-gnueabihf"
AC_ARG_WITH(svn-lib,
[[  --with-svn-lib=DIR  Use the given path to the subversion libraries.]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        SVN_LIBS=$withval
    fi
])
AC_MSG_CHECKING([for Subversion libraries])
SVN_LIB=""
for VALUE in $SVN_LIBS ; do
  if ls $VALUE/libsvn_client-1.* >/dev/null 2>&1; then
    SVN_LIB=$VALUE
    break
  fi
done
if test $SVN_LIB ; then
    AC_MSG_RESULT([found])
else
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Subversion libraries are required. Try --with-svn-lib.])
fi
SVN_LIBS="-L$SVN_LIB -lsvn_client-1 -lsvn_wc-1 -lsvn_ra-1 -lsvn_delta-1 -lsvn_subr-1"

dnl
dnl wxWidgets
dnl

WX_CONFIGS="wx-config"
AC_ARG_WITH(wx-config,
[[  --with-wx-config=FILE     Use the given path to wx-config when determining
                            wxWidgets configuration; defaults to "wx-config"]],
[
    if test "$withval" != "yes" -a "$withval" != ""; then
        WX_CONFIGS=$withval
    fi
])
AC_MSG_CHECKING([wxWidgets version])
WX_CONFIG=""
for VALUE in $WX_CONFIGS ; do
  if WX_VERSION=`$VALUE --version 2>&1` ; then
    WX_CONFIG=$VALUE
    break
  fi
done
if test $WX_CONFIG ; then  
  AC_MSG_RESULT([$WX_VERSION])
else
  AC_MSG_RESULT([not found])
  AC_MSG_ERROR([wxWidgets is required. Try --with-wx-config.])
fi
case $WX_VERSION in
    [2.4.[2-9]])
        ;;
    [2.[5-9].*])
        ;;
    [3.0.*])
        ;;
    *)
        AC_MSG_ERROR([wxWidgets >= 2.4.2 required, found version $WX_VERSION])
        AC_MSG_ERROR([Try --with-wx-config.])
        ;;
esac
CPPFLAGS="$CPPFLAGS `$WX_CONFIG --cppflags`"
CXXFLAGS="$CXXFLAGS `$WX_CONFIG --cxxflags | sed -e 's/-fno-exceptions//'`"
WX_LIBS="`$WX_CONFIG --libs base,core,adv`"

dnl
dnl Platform specific specials
dnl
AC_MSG_CHECKING([for platform specifics])
EXTRA_LIBS=""
case "$target" in
    *-*-darwin* )
        AC_MSG_RESULT([darwin])
        EXTRA_LIBS="-framework Security"
        ;;
    *)
        AC_MSG_RESULT([no])
        ;;
esac

dnl
dnl CppUnit
dnl 
CPPUNITCONFIG="cppunit-config"
AC_ARG_WITH(cppunit-config,
[[  --with-cppunit-config=FILE     Use the given path to cppunit-config
                            when determining the cpp Unit configuration; 
                            defaults to ""]],
[
  if test "$withval" = "no"; then
    CPPUNITCONFIG=
  elif test "$withval" != "yes"; then
    CPPUNITCONFIG=$withval
  fi
])
AC_MSG_CHECKING([cppunit-config])
if test -z "$CPPUNITCONFIG" ; then
  AC_MSG_RESULT([not used])
else
  if $CPPUNITCONFIG --version > /dev/null 2>&1; then
    AC_MSG_RESULT([found])
  else
    AC_MSG_RESULT([not found])
    CPPUNITCONFIG=
  fi
fi

dnl
dnl XsltProc
dnl 
XSLTPROC=xsltproc
AC_ARG_WITH(xsltproc,
[[  --with-xsltproc=FILE     Use the given path to xsltproc; 
                            defaults to "xsltproc"]],
[
  if test "$withval" = "no"; then
    XSLTPROC=
  elif test "$withval" != "yes"; then
    XSLTPROC=$withval
  fi
])
AC_MSG_CHECKING([xsltproc])
if test -z "$XSLTPROC" ; then
  AC_MSG_RESULT([not used])
else
  if $XSLTPROC --version >/dev/null 2>&1 ; then
    AC_MSG_RESULT([found])
  else
    AC_MSG_RESULT([not found])
    XSLTPROC=""
  fi
fi

dnl
dnl Docbook XSL Manpage Stylesheet
dnl
DOCBOOK_MANPAGES=yes
AC_ARG_WITH(docbook-xsl-manpages,
[[  --with-docbook-xsl-manpages=FILE   Determine the location of the
                                     DocBook XSL manpages stylesheet,
                                     needed for manpage generation.
                                     REMARK: do not supply something like
                                     /.../html/docbook.xsl. The path has
                                     to look like /.../manpages/docbook.xsl,
                                     otherwise you are using the wrong stylesheet
                                     resulting in an invalid manpage]],
[
  if test "$withval" = "no"; then
    DOCBOOK_MANPAGES=
  else
    DOCBOOK_MANPAGES=$withval
  fi
])

dnl search for Docbook XSL in standard places
dnl remark: I didnt use a list if files for usage in
dnl         a for .. do .. done loop since the line
dnl         got too long (file not found error while
dnl         executing)
if test "$DOCBOOK_MANPAGES" = "yes"; then
  X1=/usr/share/xml/docbook/stylesheet/nwalsh/manpages/docbook.xsl
  X2=/usr/share/sgml/docbook/stylesheet/xsl/nwalsh/manpages/docbook/docbook.xsl
  X3=/usr/share/sgml/docbook/yelp/docbook/manpages/docbook.xsl
  X4=/usr/share/sgml/docbook/xsl-stylesheets/manpages/docbook.xsl
  X5=/usr/local/share/sgml/docbook/stylesheet/xsl/nwalsh/manpages/docbook.xsl
  X6=/usr/local/share/sgml/docbook/yelp/docbook/manpages/docbook.xsl
  X7=/usr/share/docbook-xsl/manpages/docbook.xsl
  X8=/usr/share/xml/docbook/stylesheet/nwalsh/current/manpages/docbook.xsl
  X9=/usr/share/sgml/docbook/xsl-stylesheets*/manpages/docbook.xsl

  DOCBOOK_MANPAGES=notfound

  if test -f $X1; then
    DOCBOOK_MANPAGES=$X1
  elif test -f $X2; then
    DOCBOOK_MANPAGES=$X2
  elif test -f $X3; then
    DOCBOOK_MANPAGES=$X3
  elif test -f $X4; then
    DOCBOOK_MANPAGES=$X4
  elif test -f $X5; then
    DOCBOOK_MANPAGES=$X5
  elif test -f $X6; then
    DOCBOOK_MANPAGES=$X6
  elif test -f $X7; then
    DOCBOOK_MANPAGES=$X7
  elif test -f $X8; then
    DOCBOOK_MANPAGES=$X8
  else
    for X in $X9 ; do
      if test -f $X; then
        DOCBOOK_MANPAGES=$X
        break
      fi
    done
  fi
fi
AC_MSG_CHECKING([docbook xsl stylesheet for manpages])
if test -z "$DOCBOOK_MANPAGES"; then
   AC_MSG_RESULT([not used])
elif test -f "$DOCBOOK_MANPAGES"; then
   AC_MSG_RESULT([found ($DOCBOOK_MANPAGES)])
else
   AC_MSG_RESULT([not found])
   DOCBOOK_MANPAGES=""
fi


dnl
dnl Manpage
dnl
MANPAGE=yes
AC_ARG_WITH(manpage,
[[  --with-manpage=yes|no   Enable/disable manpage creation]],
[
  if test "$withval" != "yes"; then
    MANPAGE=no
  fi
])
TARGET_MANPAGE=manpage-no
MAN_MANS=
AC_MSG_CHECKING([manpage creation])
if test "$MANPAGE" = "no"; then
  AC_MSG_RESULT([no])
elif test "$XSLTPROC" -a "$DOCBOOK_MANPAGES" ; then
  AC_MSG_RESULT([yes])
  TARGET_MANPAGE=manpage-yes
  MAN_MANS=rapidsvn.1
else
   AC_MSG_RESULT([no (xsltproc and docbook-xsl with manpage support needed)])
fi

dnl
dnl Doxygen
dnl 
DOXYGEN=doxygen
AC_ARG_WITH(doxygen,
[[  --with-doxygen=FILE     Use the given path to doxygen.
                          Used for creating API documentation; 
                          defaults to "doxygen"]],
[
  if test "$withval" = "no"; then
    DOXYGEN=
  elif test "$withval" != "yes"; then
    DOXYGEN=$withval
  fi
])
AC_MSG_CHECKING([doxygen])
if test -z "$DOXYGEN" ; then
   AC_MSG_RESULT([not used])
else
  if doxygenversion=`$DOXYGEN --version 2>&1` ; then
    AC_MSG_RESULT([found])
  else
    AC_MSG_RESULT([not found])
    DOXYGEN=""
  fi
fi

dnl
dnl Dot (Graphviz)
dnl 
DOT=dot
AC_ARG_WITH(dot,
[[  --with-dot=FILE     Use the given path to dot. 
                      This tool is needed by doxygen; 
                      defaults to "dot"]],
[
  if test "$withval" = "no"; then
    DOT=
  elif test "$withval" != "yes"; then
    DOT=$withval
  fi
])
AC_MSG_CHECKING([dot])
if test -z "$DOT" ; then
  AC_MSG_RESULT([not used])
else
  if dotbla=`echo | $DOT 2>/dev/null` ; then
    AC_MSG_RESULT([found])
  else
    AC_MSG_RESULT([not found])
    DOT=""
  fi
fi

dnl
dnl Final check for Doxygen
dnl
if test "$DOXYGEN" ; then
  AC_MSG_CHECKING([if doxygen is usable])
  if test -z "$DOT" ; then
    AC_MSG_RESULT([no (dot needed)])
    DOXYGEN=""
  else
    AC_MSG_RESULT([yes])
  fi
fi

if test "$DOXYGEN" ; then
   TARGET_DOXYGEN="doxygen-yes"
   DOXYGEN_DIST="svncpp.dox html/*"
else 
   TARGET_DOXYGEN="doxygen-no"
   DOXYGEN_DIST=
fi

AC_SUBST(APR_LIBS)
AC_SUBST(WX_LIBS)
AC_SUBST(SVN_LIBS)
AC_SUBST(EXTRA_LIBS)
AC_SUBST(DOCBOOK_MANPAGES)
AC_SUBST(XSLTPROC)
AC_SUBST(TARGET_MANPAGE)
AC_SUBST(MAN_MANS)
AC_SUBST(DOXYGEN)
AC_SUBST(DOXYGEN_DIST)
AC_SUBST(TARGET_DOXYGEN)
AC_SUBST(SVNCPP_DIR)
AC_SUBST(LIBRAPIDSVN_DIR)

if test "$CPPUNITCONFIG" ; then
    CPPUNIT_CXXFLAGS="`$CPPUNITCONFIG --cflags`"
    CPPUNIT_LIBS="`$CPPUNITCONFIG --libs`"
    AC_SUBST(CPPUNIT_LIBS)
    AC_SUBST(CPPUNIT_CXXFLAGS)
fi

AC_OUTPUT(Makefile \
          build/Makefile \
          build/vc2005/Makefile \
          build/xcode/Makefile \
          doc/Makefile \
          doc/manpage/Makefile \
          doc/svncpp/Makefile \
          libsvncpp/Makefile \
          libsvncpp/tests/Makefile \
          librapidsvn/Makefile \
          librapidsvn/src/locale/Makefile \
          librapidsvn/src/res/bitmaps/Makefile \
          librapidsvn/tests/Makefile \
          packages/Makefile \
          packages/debian/Makefile \
          packages/osx/Makefile \
          packages/rpm/Makefile \
          packages/win32/Makefile \
          rapidsvn/Makefile \
          tools/Makefile)

