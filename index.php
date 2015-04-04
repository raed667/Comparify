<!DOCTYPE html>
<html>
    <head>
        <title>CMP</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <style>
            body { padding:0px; margin:0px; }
            #ajax_div { position: relative; float: left; width: 100%; height: 100%; }

        </style>


        <div>

            <?php
            $allFiles = scandir("./dataset");
            unset($allFiles[0]);
            unset($allFiles[1]);
            $selectedFiles = array_rand($allFiles, 16);

            foreach ($selectedFiles as $value) {
                ?>
                <img id="<?php echo $allFiles[$value] ?>" name="<?php echo $allFiles[$value] ?>" height="128" width="128" src="./dataset/<?php echo $allFiles[$value] ?>" />
            <?php }
            ?>     

        </div>
        <div id="ajax_div"></div>
        <hr>
        <div>
            <img id="im1" height="255" width="255">
            <img id="im2" height="255" width="255">
            <img id="im3" height="255" width="255">
            <div id="req"></div>
        </div> 

        <script src="js/libs/jquery/jquery.min.js"></script>
        <script>
            $(document).ready(function () {
                // $("#loader").hide();
                $(document).ajaxStart(function () {
                    $("#loader").show();
                }).ajaxStop(function () {
                    $("#loader").hide();
                });

                $("img").click(function (event) {
                    $("#im1").removeAttr("src");
                    $("#im2").removeAttr("src");
                    $("#im3").removeAttr("src");

                    $('#ajax_div').html('<img src="loader.gif" />');
                    $.post("worker.php",
                            {
                                id: "" + event.target.id
                            },
                    function (data, status) {
                        //alert("Data: " + data + "\nStatus: " + status);
                        var obj = jQuery.parseJSON(data);
                        $('#ajax_div').html('');

                        if (obj[1] >= 0.4) {
                            $("#im1").attr("src", "./dataset/" + obj[0]);
                        }
                        if (obj[3] >= 0.4) {
                            $("#im2").attr("src", "./dataset/" + obj[2]);
                        }
                        if (obj[5] >= 0.4) {
                            $("#im3").attr("src", "./dataset/" + obj[4]);
                            //  alert(obj[1]+" "+obj[3]+" "+obj[5]+" ");
                        }
                        $("#req").html(obj[1] + "-" + obj[3] + "-" + obj[5]);
                    });
                });
            });
        </script>
    </body>
</html>

