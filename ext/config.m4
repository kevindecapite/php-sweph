PHP_ARG_ENABLE(
    [swephp],
    [whether to enable the swephp extension],
    [AS_HELP_STRING(
        [--enable-swephp],
        [Enable the Swiss Ephemeris PHP extension]
    )],
    [no]
)

PHP_ARG_WITH(
    [swisseph-src],
    [path to the Swiss Ephemeris source directory],
    [AS_HELP_STRING(
        [--with-swisseph-src=DIR],
        [Path containing swephexp.h and libswe.a]
    )],
    [no],
    [no]
)

if test "$PHP_SWEPHP" != "no"; then
    if test "$PHP_SWISSEPH_SRC" = "no" || test -z "$PHP_SWISSEPH_SRC"; then
        AC_MSG_ERROR([
Swiss Ephemeris source directory missing.

Use:

  --with-swisseph-src=/path/to/swisseph
        ])
    fi

    SWISSEPH_SRC_DIR="$PHP_SWISSEPH_SRC"

    AC_MSG_NOTICE([Swiss Ephemeris source directory: $SWISSEPH_SRC_DIR])

    if test ! -d "$SWISSEPH_SRC_DIR"; then
        AC_MSG_ERROR([
Swiss Ephemeris directory not found:

  $SWISSEPH_SRC_DIR
        ])
    fi

    if test ! -f "$SWISSEPH_SRC_DIR/swephexp.h"; then
        AC_MSG_ERROR([
swephexp.h not found in:

  $SWISSEPH_SRC_DIR
        ])
    fi

    if test ! -f "$SWISSEPH_SRC_DIR/libswe.a"; then
        AC_MSG_ERROR([
libswe.a not found in:

  $SWISSEPH_SRC_DIR
        ])
    fi

    PHP_ADD_INCLUDE([$SWISSEPH_SRC_DIR])

    dnl Statische Swiss-Ephemeris-Bibliothek direkt verlinken.
    SWEPHP_SHARED_LIBADD="$SWISSEPH_SRC_DIR/libswe.a"
    PHP_SUBST([SWEPHP_SHARED_LIBADD])

    dnl Wichtig: Hier muss $ext_shared verwendet werden.
    PHP_NEW_EXTENSION(
        [swephp],
        [swephp.c],
        [$ext_shared],
        [],
        [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1]
    )

    AC_DEFINE(
        [HAVE_SWEPHP],
        [1],
        [Define to 1 if the swephp extension is enabled]
    )
fi