<!DOCTYPE html>
<html>
    <head>
        <title>CMP</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <div id="ajax_div"></div>

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
        <div>
            <img id="im1" height="255" width="255">
            <img id="im2" height="255" width="255">
            <img id="im3" height="255" width="255">
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
                    $('#ajax_div').html('<img src="loader.gif" />');
                    $.post("worker.php",
                            {
                                id: "" + event.target.id
                            },
                    function (data, status) {
                        //alert("Data: " + data + "\nStatus: " + status);
                        var obj = jQuery.parseJSON(data);
                        $("#im1").attr("src", "./dataset/" + obj[0]);
                        $("#im2").attr("src", "./dataset/" + obj[1]);
                        $("#im3").attr("src", "./dataset/" + obj[2]);
                        $('#ajax_div').html('');
                    });
                });
            });
        </script>
    </body>
</html>

