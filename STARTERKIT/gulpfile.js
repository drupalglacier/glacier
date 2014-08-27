// Load plugins
var path         = require('path');
var gulp         = require('gulp');
var autoprefixer = require('gulp-autoprefixer');
var cssshrink    = require('gulp-cssshrink');
var livereload   = require('gulp-livereload');
var minifyCSS    = require('gulp-minify-css');
var rename       = require('gulp-rename');
var sass         = require('gulp-ruby-sass');
var gutil        = require('gulp-util');
var penthouse    = require('penthouse');

// Styles
gulp.task('styles', function () {
  return gulp.src('scss/**/*.scss')
    .pipe(sass({ style: 'compact', precision: 7, sourcemap: true }))
    .on('error', gutil.log)
    .pipe(autoprefixer('last 2 versions', 'safari 5', 'ie 8', 'ie 9', 'ios 6', 'android 4'))
    .on('error', gutil.log)
    .pipe(gulp.dest('css'));
});

// Minify
gulp.task('minify', ['styles'], function () {
  return gulp.src('css/style.css')
    .pipe(minifyCSS())
    .pipe(cssshrink())
    .pipe(rename(function (path) {
      path.basename += '.min';
    }))
    .pipe(gulp.dest('css'))
    .pipe(livereload());
});

// Critical
gulp.task('critical', ['minify'], function () {
  console.warn('Set penthouse url in gulpfile.js and delete this message!');
  penthouse({
    url : 'http://website.com/',
    css : path.join('css/style.min.css'),
    width : 480,
    height : 640
  }, function(err, criticalCss) {
    string_src('critical.min.css', criticalCss)
      .pipe(gulp.dest('css'));
  });
});

// Watch Styles
gulp.task('watch', function () {
  gulp.watch('scss/**/*.scss', ['styles', 'minify', 'critical']);
  gulp.watch('../../libraries/avalanche/src/**/*.scss', ['styles', 'minify', 'critical']);
});

// Default task
gulp.task('default', function () {
  gulp.start('watch');
});

//
function string_src(filename, string) {
  var src = require('stream').Readable({ objectMode: true })
  src._read = function () {
    this.push(new gutil.File({ cwd: "", base: "", path: filename, contents: new Buffer(string) }));
    this.push(null);
  }
  return src;
}