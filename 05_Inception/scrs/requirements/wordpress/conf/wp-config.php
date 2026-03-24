<?php
define( 'DB_NAME', getenv('MYSQL_DATABASE'));


define( 'DB_USER', getenv('MYSQL_USER'));


define( 'DB_PASSWORD', getenv('MYSQL_PASSWORD'));


define( 'DB_HOST', getenv('MYSQL_HOST'));


define( 'DB_CHARSET', 'utf8mb4' );
define( 'DB_COLLATE', '' );

define( 'AUTH_KEY',         getenv('WP_AUTH_KEY'));
define( 'SECURE_AUTH_KEY',  getenv('WP_SECURE_AUTH_KEY'));
define( 'LOGGED_IN_KEY',    getenv('WP_LOGGED_IN_KEY'));
define( 'NONCE_KEY',        getenv('WP_NONCE_KEY'));
define( 'AUTH_SALT',        getenv('WP_AUTH_SALT'));
define( 'SECURE_AUTH_SALT', getenv('WP_SECURE_AUTH_SALT'));
define( 'LOGGED_IN_SALT',   getenv('WP_LOGGED_IN_SALT'));
define( 'NONCE_SALT',       getenv('WP_NONCE_SALT'));

$table_prefix = 'wp_';

define( 'WP_DEBUG', false );

if (getenv('WP_REDIS_HOST')) {
    define('WP_REDIS_HOST', getenv('WP_REDIS_HOST'));
    define('WP_CACHE', true);
}

if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

require_once ABSPATH . 'wp-settings.php';