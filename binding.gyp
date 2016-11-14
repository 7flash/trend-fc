 {
   "targets": [
     {
       "target_name": "flat-contours",
       "sources": [ "flat-contours.cpp" ],
        "include_dirs": [
            "<!(node -e \"require('nan')\")",
        ]
     }
   ]
}