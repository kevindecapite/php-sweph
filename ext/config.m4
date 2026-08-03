dnl config.m4 for extension swephp

PHP_ARG_WITH([sweph],
  [for Swiss Ephemeris (libswe) support],
  [AS_HELP_STRING([--with-sweph],
    [Include Swiss Ephemeris support])])

if test "$PHP_SWEPH" != "no"; then

  dnl Automatisches Bauen der statischen Bibliothek libswe.a, falls nötig
  if ! test -r "$ext_srcdir/src/libswe.a"; then
    AC_MSG_RESULT([Building libswe.a in $ext_srcdir/src])
    (cd "$ext_srcdir/src" && make libswe.a)
  fi

  if test -r "$ext_srcdir/src/libswe.a"; then
    SWEPH_DIR="$ext_srcdir/src"
    AC_MSG_RESULT([libswe.a found in $SWEPH_DIR])
  else
    AC_MSG_ERROR([libswe.a not found! Please make sure Swiss Ephemeris sources are present in src/])
  fi

  dnl Header-Pfad hinzufügen
  PHP_ADD_INCLUDE($SWEPH_DIR)

  dnl Statische Bibliothek & Mathe-Bibliothek sauber zu den Modul-Linkerflags hinzufügen
  PHP_ADD_LIBRARY_WITH_PATH(swe, $SWEPH_DIR, SWEPHP_SHARED_LIBADD)
  PHP_ADD_LIBRARY(m,, SWEPHP_SHARED_LIBADD)

  PHP_SUBST(SWEPHP_SHARED_LIBADD)

  dnl Extension definieren
  PHP_NEW_EXTENSION(swephp, swephp.c, $ext_shared)
fi