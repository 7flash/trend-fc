var express = require('express');
var router = express.Router();

var fc = require('bindings')('flat-contours');

router.get('/', function (req, res, next) {
    res.render('index', {title: 'Upload file'});
});

router.post("/upload", function (req, res) {
    if (!req.files.cropped || !req.files.source) {
        return res.render('index', {title: 'Fail'});
    }
    var cropped = req.files.cropped;
    var source = req.files.source;
    var croppedPath = 'uploads/cropped/' + cropped.name;
    var sourcePath = 'uploads/source/' + source.name;
    var resultPath = 'uploads/result/' + source.name;
    cropped.mv(croppedPath, function (err) {
        if (err) console.error(err);
        else {
            source.mv(sourcePath, function (err) {
                if (err) console.error(err);
                else {
                    fc.processImages(croppedPath, sourcePath, resultPath, function(result) {
                        console.log('RESULT: '+result);
                    });
                }
            });
        }
    });
    res.render('index', {title: 'Success'});
});

module.exports = router;