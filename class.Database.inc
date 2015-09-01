<?php

/* 
 * Written For Meditech.
 * Author: Kevin Crosby
 * KCROSBY@MEDITECH.COM
 * EXT: 3042
 */

class Database{
    
    private $_connection;
    private static $_instance;
    
    public static function getInstance(){
        if(!self::$_instance){
            self::$_instance = new self();
        }
       return self::$_instance; 
     }
    
     public function __construct() {
             /*** connect to database ***/
    /*** mysql hostname ***/
    $mysql_hostname = 'localhost';

    /*** mysql username ***/
    $mysql_username = 'root';

    /*** mysql password ***/
    $mysql_password = '';

    /*** database name ***/
    $mysql_dbname = 'databaseTest';

            $this->_connection = new PDO("mysql:host=$mysql_hostname;dbname=$mysql_dbname", $mysql_username, $mysql_password);
        /*** $message = a message saying we have connected ***/

        /*** set the error mode to excptions ***/
        //$this->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        
         //error handling
         if(mysqli_connect_error()){
             trigger_error('failed to connect to MySQL: '. mysqli_connect_error(), E_USER_ERROR);
         }
     }
     
     /**
      * empty clone method to prevent duplication'
      * 
      */
     private function __clone() {}
     
     public function getConnection(){
         return $this->_connection;
     }
    
}

