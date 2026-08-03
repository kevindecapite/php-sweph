dnl config.m4 for the swephp extension

PHP_ARG_ENABLE(
  [swephp],
  [whether to enable the swephp extension],
  [AS_HELP_STRING(
    [--enable-swephp],
    [Enable the Swiss Ephemeris PHP extension]
  )],
  [no],
  [yes]
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
  if test "$PHP_SWISSEPH_SRC" = "no" \
    || test -z "$PHP_SWISSEPH_SRC"; then
    AC_MSG_ERROR([
Swiss Ephemeris source directory missing.

Use:

  ./configure \
    --enable-swephp=shared \
    --with-swisseph-src=/app/native/swisseph
    ])
  fi

  SWISSEPH_SRC_DIR="$PHP_SWISSEPH_SRC"

  AC_MSG_NOTICE([
Swiss Ephemeris source directory:

  $SWISSEPH_SRC_DIR
  ])

  AS_IF(
    [test ! -d "$SWISSEPH_SRC_DIR"],
    [AC_MSG_ERROR([
Swiss Ephemeris source directory not found:

  $SWISSEPH_SRC_DIR
    ])]
  )

  AS_IF(
    [test ! -f "$SWISSEPH_SRC_DIR/swephexp.h"],
    [AC_MSG_ERROR([
swephexp.h not found in:

  $SWISSEPH_SRC_DIR
    ])]
  )

  AS_IF(
    [test ! -f "$SWISSEPH_SRC_DIR/libswe.a"],
    [AC_MSG_ERROR([
libswe.a not found in:

  $SWISSEPH_SRC_DIR
    ])]
  )

  PHP_ADD_INCLUDE([$SWISSEPH_SRC_DIR])

  dnl libswe.a direkt an das Shared-Modul linken.
  SWEPHP_SHARED_LIBADD="$SWISSEPH_SRC_DIR/libswe.a"
  PHP_SUBST([SWEPHP_SHARED_LIBADD])

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