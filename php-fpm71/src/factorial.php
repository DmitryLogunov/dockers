<?php
if( !$_GET[number] ) {
  echo "Should define number for factorial calculating ( /factorial.php?number=xxx)";
  exit;
}

function factorial($num) {
     $out = "";
     $res = array();
     $carry = 0;

     $res[0] = 1;
     for($i=2; $i <= $num; $i++){
       for($j=0; $j < sizeof($res); $j++){
         $tmp=$res[$j]*$i;
         $res[$j]=($tmp + $carry)%10 ;
         $carry=($tmp + $carry)/10;
       }
       while($carry!=0) {
         $res[] = $carry%10;
         $carry = $carry/10;
       }
     }

     $length_out = sizeof($res)-1;
     for($i = sizeof($res)-1; $i >= 0; $i--) {
        if ( $res[$i] != 0 ) { $length_out = $i; break; }
     }
     for($i = $length_out; $i >= 0; $i--) $out = $out.strval($res[$i]);

     return $out;
}

echo factorial((int)$_GET[number])."\n\r";

//echo gmp_fact((int)$_GET[number]);
?>