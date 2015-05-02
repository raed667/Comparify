function showValue(newValue)
{
    document.getElementById("range").innerHTML = newValue + "%";
    $('.img-result').each(function (i, obj) {
        var val = parseFloat($(this).attr("alt"));
        val *= 100;
        if (newValue <= val) {
            $(this).show(500);
        } else {
            $(this).hide();
        }
    });
}

function check() {
    var x = document.getElementById("myCheck1").checked;
    var y = document.getElementById("myCheck2").checked;

    var range = document.getElementById("slide").value;


    if ($('#img-chosen').attr('src') == "http://placehold.it/250x250&text=Choose+an+Image") {
        $("#no-image").show(500);
        return;
    } else {
        $("#no-image").hide(500);
    }


    //  alert("Checkbox1 : " + x + "\n" + "Checkbox2 : " + y + "\n" + "Checkbox3 : " + z + "\n" + "Range :" + range);
    $('.img-results').html('');
    if (x || y) {
        $('#ajax_div').html('<img class="loader" src="loader.gif" />');
        $('.img-rand').hide(1000);
        $("#no-method").hide(500);

    } else {
        $("#no-method").show(500);
    }
    var Xdone = false;
    var Ydone = false;

    /// HISTOGRAMME
    if (x)
    {
        var htime1 = Date.now();
        //    alert($('img[id="img-chosen"]').attr('alt'));
        $.post("worker.php",
                {
                    id: "" + $('img[id="img-chosen"]').attr('alt')
                },
        function (data, status) {

            var obj = jQuery.parseJSON(data);
            for (var i = 0, max = obj.length; i < max; i++) {

                var disp = "display: inline;";
                var rat = parseFloat(obj[i].ratio) * 100;
                if (range > rat) {
                    disp = "display: none;";
                }

                $('#Hist').append($('<img>', {style: disp, alt: obj[i].ratio, id: "found_" + obj[i].pic, class: "img-result", src: 'http://localhost/cmp/dataset/' + obj[i].pic}));
            }

        }).done(function () {
            var totalHTime = Date.now() - htime1;
            $("#htime").html("(" + (totalHTime / 1000) + "s)");
            Xdone = true;
            if (Ydone) {
                $('#ajax_div').html('');
                $('.img-rand').show(1000);

            }
            //  alert();
            // Here I want to get the how long it took to load some.php and use it further
        });
    } else {
        Xdone = true;
    }

/// FORMES

    if (y)
    {
        var ptime1 = Date.now();

        var val = range / 100;
        // alert($('img[id="img-chosen"]').attr('alt'));
        $.post("worker2.php",
                {
                    id: "" + $('img[id="img-chosen"]').attr('alt'),
                    ratio: val
                },
        function (data) {

            var obj = jQuery.parseJSON(data);
            for (var i = 0, max = obj.length; i < max; i++) {

                var disp = "display: inline;";
                var rat = parseFloat(obj[i].ratio) * 100;
                if (range > rat) {
                    disp = "display: none;";
                }

                $('#Form').append($('<img>', {style: disp, alt: obj[i].ratio, id: "found_" + obj[i].pic, class: "img-result", src: 'http://localhost/cmp/dataset/' + obj[i].pic}));
            }

        }).done(function () {
            var totalPTime = Date.now() - ptime1;
            $("#ptime").html("(" + (totalPTime / 1000) + "s)");
            Ydone = true;

            if (Xdone) {
                $('#ajax_div').html('');
                $('.img-rand').show(500);
            }

            //  alert();
            // Here I want to get the how long it took to load some.php and use it further
        });
    } else {
        Ydone = true;
    }




}

$(document).ready(function () {
    $('#ref').click(function () {
        $("#no-image").hide(500);
        $("#no-method").hide(500);

        $('#myCheck1').prop('checked', false);
        $('#myCheck2').prop('checked', false);
        $('#myCheck3').prop('checked', false);
        $('#slide').val(0);
        $('#range').text(0);

        $('.result').html('');
        $.get("http://localhost/cmp/getRandom16.php", function (data) {
            var images = data.images;
            for (var i = 0, max = images.length; i < max; i++) {
                $(".result").prepend($('<img>', {id: images[i], class: "img-rand", src: 'http://localhost/cmp/dataset/' + images[i]}))
            }
        });

    });
    $.get("http://localhost/cmp/getRandom16.php", function (data) {
        var images = data.images;
        for (var i = 0, max = images.length; i < max; i++) {
            $(".result").prepend($('<img>', {id: images[i], class: "img-rand", src: 'http://localhost/cmp/dataset/' + images[i]}))
        }
    });
    $(document).on("click", ".img-rand", function (event) {
//   alert(event.target.id);
        var source = "http://localhost/cmp/dataset/" + event.target.id
        $("#img-chosen").attr("src", source);
        $("#img-chosen").attr("alt", event.target.id);
    });

    $("#no-image").hide();
    $("#no-method").hide(500);


});









