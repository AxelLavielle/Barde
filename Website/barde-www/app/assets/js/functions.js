;(function ($, window, document, undefined) {
    var $win = $(window);
    var $doc = $(document);

    function initMaps() {
        $('.googlemap').each(function () {
            var centerLat = parseFloat($(this).data('lat'));
            var centerLng = parseFloat($(this).data('lng'));

            var myLatLng = {lat: centerLat, lng: centerLng};

            var mapOptions = {
                center: myLatLng,
                zoom: 17,
                mapTypeId: google.maps.MapTypeId.roadmap,
                scrollwheel: false
            }

            map = new google.maps.Map(this, mapOptions);

            var marker = new google.maps.Marker({
                position: myLatLng,
                map: map,
                icon: {
                    url: 'css/images/temp/logo-marker.png',
                    size: new google.maps.Size(194, 58),
                    origin: new google.maps.Point(0, 0),
                    anchor: new google.maps.Point(90, 32)
                }
            });

            if ($(this).data('draggable') === true) {
                marker.setDraggable(true);
                marker.setIcon(null);
            }

        });
    }

    window.initMaps = initMaps;

    $doc.ready(function () {
        $('.btn-menu').on('click', function (event) {
            $('.wrapper-inner').toggleClass('moved');
            $('html').toggleClass('fixed');
            $('.nav-holder').toggleClass('show');

            $('.header > .btn-menu').toggleClass('hide');

            event.preventDefault();
        });

        $('.link-scroll').on('click', function () {
            var $this   = $(this);
            var $parent = $this.closest('.intro');
            var target  = $parent.next('.section');

            $("html, body").animate({
                scrollTop: $(target).offset().top
            }, 1200);

            return false;
        });


        $(".cross").hide();
        $(".menu-mobile").hide();
        $(".hamburger").click(function () {
            $(".hamburger").hide();
            $(".cross").show();
            $('.menu-mobile').addClass('show');

            $(".menu-mobile").slideToggle("slow", function () {
            });
        });

        $(".cross").click(function () {
            $(".cross").hide();
            $(".hamburger").show();

            $(".menu-mobile").slideToggle("slow", function () {
                $('.menu-mobile').removeClass('show');

            });

        });

    });

    var mn  = $(".nav");
    var mns = "nav-scroll";
    var hdr = $(window).height();

    $(window).scroll(function () {
        if ($(this).scrollTop() > hdr - 100) {
            $('.nav-scroll').addClass('show');
            $('.nav-scroll-mobile').addClass('show');
            $('.menu-mobile').addClass('show');
        } else {
            $('.nav-scroll').removeClass('show');
            $('.nav-scroll-mobile').removeClass('show');
            $('.menu-mobile').removeClass('show');
        }
    });


})(jQuery, window, document);
