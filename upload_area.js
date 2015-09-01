document.addEventListener('drop',function(event){
            event.stopPropagation();
        event.preventDefault();
},false);

function add_upload(id) {
    var dropArea = document.getElementById(id);
    var nextFile = '';
    var stoppoll = null;
    var imgloadheight = 0;
    var list = [];
    var totalSize = 0;
    var totalProgress = 0;
    var starttime = 0;
    var endtime = 0;
    var pollprogress = 0;
    var totaltime = 0;
    var timeperchunk = 1220;


    dropArea.addEventListener('drop', handleDrop, false);
    dropArea.addEventListener('dragover', handleDragOver, false);
    $(dropArea).bind('mouseleave', over_upload);

    function over_upload(e) {
        if (!$('.hover_upload').length)
            return;
        $('.hover_upload').each(function () {
            if (this !== e.target) {
                $(this).removeClass('hover_upload');
            }
        });
    }



    // drag over
    function handleDragOver(event) {
        event.stopPropagation();
        event.preventDefault();
        $('.hover_upload').each(function () {
            $(this).removeClass('hover_upload');
        });
        $(event.target).addClass('hover_upload');
    }

    // drag drop
    function handleDrop(event) {
        event.stopPropagation();
        event.preventDefault();
        upload_new_image(event.dataTransfer.files, event.target);
        $('.hover_upload').each(function () {
            $(this).removeClass('hover_upload');
        });
    }



    function processFiles(filelist) {

        if (!filelist || !filelist.length || list.length)
            return;
        for (var i = 0; i < filelist.length; i++) {
            list.push(filelist[i]);
        }
        return list;
    }

    var imgPre;
    var canvImg;
    function upload_new_image(files, element) {

        var image_list = processFiles(files);
        var image = image_list.shift();
        var reader = new FileReader();
        reader.onload = function (evt) {
            var prodImg = new Image();
            prodImg.src = evt.target.result;
            $("#product-image-target").append(prodImg);

            $("#product-image-target img").Jcrop({
                onChange: showPreview,
                onSelect: showPreview,
                aspectRatio: 4 / 3
            });
            canvImg = convertImageToCanvas(prodImg);
        };
        reader.readAsDataURL(image);


    }

    function showPreview(coords)
    {
        if (coords.w > 1 && coords.h > 1) {
            var rx = $("#product-image-target img")[0].width / $("#product-image-target .jcrop-holder").width();
            var ry = $("#product-image-target img")[0].height / $("#product-image-target .jcrop-holder").height();
            var imgx = Math.round(coords.x * rx);
            var imgy = Math.round(coords.y * ry);
            var imgData = canvImg.getImageData(imgx, imgy, Math.round(coords.w * rx), Math.round(coords.h * ry));
            var canvast = document.createElement("canvas");
            canvast.height = Math.round(coords.h * ry);
            canvast.width = Math.round(coords.w * rx);
            ;
            var cx = canvast.getContext('2d');
            cx.putImageData(imgData, 0, 0);
            $('#product_img_preview').prop("src", canvast.toDataURL());

        }
    }
    function convertImageToCanvas(image) {
        var canvas = document.createElement("canvas");
        canvas.width = image.width;
        canvas.height = image.height;
        canvas.getContext("2d").drawImage(image, 0, 0);

        return canvas.getContext("2d");
    }

}

