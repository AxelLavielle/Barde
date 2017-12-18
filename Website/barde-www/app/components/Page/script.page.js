/**
 * APLT
 * < arnaud perrault />
 * barde-www - Created on 27/05/2017
 */

import Vue from 'vue'
import PageService from '../../services/PageServices'

export default {
    name: 'Page',
    data () {
        return {
            pageContent: '',
        }
    },
    mounted: function () {
        this.getPageContent()

    },
    methods: {
        getPageContent: function () {

            var page = this.$route.params.id;

            PageService.getPage(page).then(response => {

                this.pageContent = response.body.content;

                setTimeout(function() {

                    $("#img-logo").attr('width', '171');
                    $("#img-logo").attr('height', '76');

                    $("#img-logo").attr('src', '/app/assets/images/temp/logo-engineering@2x.png');
                })

                setTimeout(function () {

                    this.url = 'http://google.com';

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


                }, 500);
            }, response => {
                //error callback
            })
        }
    }
}
