AC_INIT([pusherpp], [0.5])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])
AC_MSG_NOTICE([Pusher++: A Thread-Safe C++ Server Library for Pusher])
AC_SUBST([LIBVERSION], [0.5])
AC_SUBST([SOVERSION], [0:5:0])
CXXFLAGS="$CXXFLAGS -std=c++0x"
AC_PROG_CXX
AC_LANG(C++)
LT_INIT([disable-static])

AC_CHECK_HEADER(openssl/x509.h,,[AC_MSG_ERROR([cannot find openssl header file x509.h (hint: do you have libcrypto and libcrypto-dev installed?)])])
AC_CHECK_HEADER(openssl/hmac.h,,[AC_MSG_ERROR([cannot find openssl header file hmac.h (hint: do you have libcrypto and libcrypto-dev installed?)])])
AC_CHECK_HEADER(openssl/evp.h,,[AC_MSG_ERROR([cannot find openssl header file evp.h (hint: do you have libcrypto and libcrypto-dev installed?)])])
AC_CHECK_HEADER(openssl/md5.h,,[AC_MSG_ERROR([cannot find openssl header file md5.h (hint: do you have libcrypto and libcrypto-dev installed?)])])
AC_CHECK_HEADER(curl/curl.h,,[AC_MSG_ERROR([cannot find curl header file curl.h (hint: do you have libcurl and libcurl-dev installed?)])])

AC_CHECK_LIB(crypto, MD5,,[AC_MSG_ERROR([cannot find function MD5() in libcrypto (hint: make sure you have libcrypto/openssl >= 0.0.0)])])
AC_CHECK_LIB(crypto, HMAC,,[AC_MSG_ERROR([cannot find function HMAC() in libcrypto (hint: make sure you have libcrypto/openssl >= 0.9.0)])])
AC_CHECK_LIB(crypto, EVP_sha256,,[AC_MSG_ERROR([cannot find function EVP_sha256() in libcrypto (hint: make sure you have libcrypto/openssl >= 0.9.7)])])

AC_CONFIG_HEADERS([pusherpp/include/config.h])

AC_CONFIG_FILES([Makefile pusherpp.pc])
AC_OUTPUT

# For future use...
#AC_CONFIG_FILES([Makefile pusherpp-${LIBVERSION}.pc:pusherpp.pc.in])
