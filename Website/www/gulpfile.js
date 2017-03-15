var gulp        = require('gulp'),
    concat      = require('gulp-concat'),
    uglify      = require('gulp-uglify'),
    clean       = require('gulp-clean'),
    connect     = require('gulp-connect');

gulp.task('concat-app', function() {
    return gulp .src([
        'app/components/angular.min.js',
        'app/components/angular-route.js',
        'app/components/angular-cookies.js',
        'node_modules/angular-md5/angular-md5.js',
        'node_modules/angular-materialize/src/angular-materialize.js',
        'node_modules/angular-recaptcha/release/angular-recaptcha.js',
        'app/directives/*.js',
        'app/controllers/*.js',
        'app/app.js',
        'app/services/*.js'])
          .pipe(concat('app.concat.js'))
          .pipe(gulp.dest('app/'));
});

gulp.task('concat-js', function() {
    return gulp .src([
      'node_modules/jquery/dist/jquery.js',
      'node_modules/materialize-css/bin/materialize.js',
    ])
    .pipe(concat('javascript-concat.js'))
        .pipe(gulp.dest('js/'));
});

gulp.task('concat-css', function() {
  return gulp .src([
    'css/style.css',
    'node_modules/materialize-design-icons/iconfont/material-icons.css',
    'node_modules/materialize-css/bin/materialize.css'
  ])
  .pipe(concat('style.concat.css'))
  .pipe(gulp.dest('css/'));
});

gulp.task('clean', function() {
  return gulp.src(['css/style.concat.css', 'app/app.concat.js'], {read: false})
      .pipe(clean());
});

gulp.task('serve', function() {
  connect.server();
});

gulp.task('default', ['concat-app', 'concat-js', 'concat-css']);
gulp.task('dev', ['default', 'serve']);
