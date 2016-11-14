 {
   "targets": [
     {
       "target_name": "flat-contours",
       "sources": [ "flat-contours.cpp", "flat-worker.cpp" ],
        "include_dirs": [
            "<!(node -e \"require('nan')\")",
        ]
     }
   ]
}
