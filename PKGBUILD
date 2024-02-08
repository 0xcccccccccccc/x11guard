# Maintainer: Ha Ma <0xcccc@bupt.com>
pkgname=x11guard
pkgver=1.0
pkgrel=1
pkgdesc="A simple X11 hook to notify KDE users when XGetImage is called"
arch=('x86_64')
url="http://github.com/0xcccccccccccc/x11guard"
license=('GPL')
depends=('libx11' 'libnotify')
makedepends=('cmake' 'make' 'gcc' 'git')
source=("git+$url.git")
sha256sums=('SKIP')

prepare() {
    mkdir -p "$srcdir/build"
}

build() {
    cd "$srcdir/build"

    cmake "$srcdir/$pkgname" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr
    make
}

package() {
    cd "$srcdir/build"

    make DESTDIR="$pkgdir/" install
}