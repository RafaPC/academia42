<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', 'wordpress' );

/** MySQL database password */
define( 'DB_PASSWORD', 'password' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8mb4' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         '2I_!s|MGp`IG#FG8`5zh4#3Ma-sMn#o?9jdhNriMV38,V^AuQ [Pi9T@{W I0f!6' );
define( 'SECURE_AUTH_KEY',  'gNbP%!iom0jotK1v!; ~afvBokvh~(#zNr?}hLj8|T;g#F}%oRY326MC3[&uX(b0' );
define( 'LOGGED_IN_KEY',    ')]3yP+q?Z.n<C5H$l%hKI1WF2/Rpj,o*;H!o*GlCkK+ukj$9u3rOMs<7bUv1_e3#' );
define( 'NONCE_KEY',        '_=QK-Vs6086,^rxfFl</v}wz{7/~$#:bS}Jf5Ar%$,uiwvD-]5v94P;+#DW;Q!hA' );
define( 'AUTH_SALT',        '8.}E-7?sA^*iH(w0s)W[TlY_./HCk_=<kG`3- I4+35jL[JX:k@Lc_P>x!jV1ua6' );
define( 'SECURE_AUTH_SALT', 'Qghwj!QS{!^Q`+Hf9nm;%OpXLHQ>u&~Lf7nY:nZmouwaIuG~;Kk;7~=P_L]KrDd1' );
define( 'LOGGED_IN_SALT',   '5X?tA4^RDQ^so)N;)Js`Co!nZ2T*bzMm /s7mDMq8o]B6ZL`|QX;q9|JwLIR.j)%' );
define( 'NONCE_SALT',       'sBw^wn,p];6^>/m,THZ]B~2/4y*uwe:-[f|q9@H~Att2{/?<D{5~dojd+67~QHVg' );

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
        define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';