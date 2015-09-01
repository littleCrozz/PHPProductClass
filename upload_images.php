<?php

/* 
 * Written for Moira Design
 */

session_start();
ini_set('display_errors',0);
ini_set('display_startup_errors',0);
error_reporting(-1);
ini_set('include_path',ini_get('include_path').':/home/moirastu/php/pear:');
include_once 'msd_config.php';
include_once 'msd_admin_db_conn.php54';




// Image check in place for the Icon
if (is_array($_FILES['image'])) {
   
        $known_photo_types = array(
        'image/pjpeg' => 'jpg',
        'image/jpeg' => 'jpeg',
        'image/gif' => 'gif',
        'image/bmp' => 'bmp',
        'image/png' => 'png'
    );
        


$case = $_REQUEST;
$case_name = $case['case_name'];
$case_file_name = str_replace(" ","_", $case_name) . substr(strval(time()), -6) ;


//get image info
$photos_uploaded = $_FILES['image'];
    $up_file = $photos_uploaded['tmp_name'];
    $filetype = $known_photo_types[$photos_uploaded['type']];
    if ($photos_uploaded['name']) {
        $image_filename = "image_". $case_file_name . "." . $filetype;
        if (move_uploaded_file($up_file, IMAGES . $image_filename)) {
            
             if(!is_dir('../Admin_Pages/case_studies')){
        mkdir ('../Admin_Pages/case_studies');       
            }
            
            if(!is_dir('../Admin_Pages/case_studies/img')){
        mkdir ('../Admin_Pages/case_studies/img');       
            }
            if(!is_dir('../Admin_Pages/case_studies/img/images')){
        mkdir ('../Admin_Pages/case_studies/img/images');       
            }
            copy(IMAGES . $image_filename, '../Admin_Pages/case_studies/img/images/'.$image_filename);
        
                $response = array('image' => array($image_filename));

            echo json_encode($response);
    
    
    
      }


}

}