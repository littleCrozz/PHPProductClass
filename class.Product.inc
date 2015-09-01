<?php

/**
 * Description of class
 *
 * @author KCROSBY
 */
class Product {

    public $product_id;
    private $name;
    private $long_desc;
    private $short_desc;
    private $price;
    private $icon;

    function __construct($data = array()) {
        $this->_time_created = time();
        if (!is_array($data)) {
            trigger_error('Unable to construct product with a ' . get_class($name));
        }
        if (count($data) > 0) {
            foreach ($data as $name => $value) {
                if (in_array($name, array(
                            'time_created',
                            'time_updated'
                        ))) {
                    $name = '_' . $name;
                }
                $this->$name = $value;
            }
        }
    }

    function __get($name) {
        //Attempt to return a protected property name
        $protected_property_name = '_' . $name;
        if (property_exists($this, $protected_property_name)) {
            return $this->$protected_property_name;
        }
        trigger_error('Undefined property via __get():' . $name);
        return NULL;
    }

    function __set($name, $value) {
        if ('_product' == $name) {
            $this->$name = $value;
            return;
        }
        trigger_error('Undefined or unallowed property via __set():' . $name);
    }

    //placeholder for product lookup
    /**
     * 
     * @return string
     */
    function get_product() {
        $db = Database::getInstance();
        $mysqli = $db->getConnection();
        $stmt = $mysqli->prepare("SELECT * FROM `products` WHERE id =?");
        $pid = $this->product_id;
        $stmt->bindValue(1, $pid, PDO::PARAM_INT);
        $stmt->execute();
        $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);
        $this->name = $rows[0]["name"];
        $this->long_desc = $rows[0]["long_description"];
        $this->short_desc = $rows[0]["short_description"];
        $this->icon = $rows[0]["icon"];
        $this->price = $rows[0]["pricing"];


        echo $rows;
    }

    //Polymorphism
    function __toString() {
        return $this->display();
    }

}
