/*
  +----------------------------------------------------------------------+
  | PHP Version 8.4+ Swiss Ephemeris extension                           |
  +----------------------------------------------------------------------+
  | Copyright (c) 2007-2026                                              |
  +----------------------------------------------------------------------+
  | Author: Joel Chen                                                    |
  | Contributor: Alois Treindl, drt04-dev                                |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_SWEPH_H
#define PHP_SWEPH_H

#include "php.h"

extern zend_module_entry swephp_module_entry;
#define phpext_swephp_ptr &swephp_module_entry

#define PHP_SWEPH_VERSION "2.0.0"

#ifdef PHP_WIN32
# define PHP_SWEPH_API __declspec(dllexport)
#else
# define PHP_SWEPH_API
#endif

PHP_MINIT_FUNCTION(swephp);
PHP_MSHUTDOWN_FUNCTION(swephp);
PHP_RINIT_FUNCTION(swephp);
PHP_RSHUTDOWN_FUNCTION(swephp);
PHP_MINFO_FUNCTION(swephp);

#endif /* PHP_SWEPH_H */