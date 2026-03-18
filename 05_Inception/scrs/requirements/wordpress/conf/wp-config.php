<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the website, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://developer.wordpress.org/advanced-administration/wordpress/wp-config/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** Database username */
define( 'DB_USER', 'jumarque' );

/** Database password */
define( 'DB_PASSWORD', 'new1234' );

/** Database hostname */
define( 'DB_HOST', 'mariadb' );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8mb4' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         '}W:1+F?i&AB^^@-sl2pb(93r#|.9]Q]ra0^>^8;U!sM%qgqdF}v[Z#p1n;BANC/!' );
define( 'SECURE_AUTH_KEY',  'rf[L?5b9^s9AcD(6D(Ea8Y]7Or TbqgHf OhFN2@MKe3LX<c?XfGFS =c(4DpM3i' );
define( 'LOGGED_IN_KEY',    'Bur tdAls<(?cv9+Q -W.7e;|?QB0RP-tZ(Yx)3H@B,0/7Y(D8tTc>-d<}GEIE_I' );
define( 'NONCE_KEY',        'xKpa,@Y<^qZ[Yp{{^bFl2?dCPkCMu6S*.}F`(j/b-QunW%wJ6,G(1MiPGB$=>+]_' );
define( 'AUTH_SALT',        '0$Cbq/#.& zq{^-W$`p/) E}n/PsTi9&6(Q;^T5UR|A?8vTqR3DIN2#=3;5<Sha6' );
define( 'SECURE_AUTH_SALT', 'OMDeVrY&L.lxA:g4>0MBy6z>B:y.8RU2E*Q-$YWUI}fnqqB,V|.RItPy$Dk:ov&E' );
define( 'LOGGED_IN_SALT',   'WNNHZw6$w;Y&48g^wDO:A3VC}IL` r, FssVT/s}TU1_2<r-#,aF..(Kx//mb52a' );
define( 'NONCE_SALT',       'f:b+!L81=rhqY[DK::+OUgQtcdXKIy%6#vrc`UR)_kFNA72LUo3^>W27xX_=;@=@' );

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 *
 * At the installation time, database tables are created with the specified prefix.
 * Changing this value after WordPress is installed will make your site think
 * it has not been installed.
 *
 * @link https://developer.wordpress.org/advanced-administration/wordpress/wp-config/#table-prefix
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
 * @link https://developer.wordpress.org/advanced-administration/debug/debug-wordpress/
 */
define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
