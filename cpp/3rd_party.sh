# ***********************************************************************************
# Trentino - A C++ based lightweight, non-invasive SCA runtime.
# Copyright (C) Siemens AG, 2012
# All Rights Reserved
# http://trentino.sourceforge.net/
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
# ***********************************************************************************

#!/bin/bash

# necessary folders (not a full path, but just a dir name)
DOWNLOAD_DIR="download"
BUILD_DIR="build"

# packages to be installed
BOOST_TARBALL="boost_1_47_0.tar.gz"
BOOST_MD5="ff180a5276bec773a7625cac7e2288e8"
BOOST_LINK="http://sourceforge.net/projects/boost/files/boost/1.47.0/boost_1_47_0.tar.gz"
BOOST_INSTALL_DIR="boost_1_47"

# CPPUNIT_TARBALL="cppunit-1.12.1.tar.gz"
# CPPUNIT_MD5="bd30e9cf5523cdfc019b94f5e1d7fd19"
# CPPUNIT_LINK="http://downloads.sourceforge.net/cppunit/cppunit-1.12.1.tar.gz"
# CPPUNIT_INSTALL_DIR="cppunit-1.12.1"

LOG4CPLUS_TARBALL="log4cplus-1.0.4.tar.bz2"
LOG4CPLUS_MD5="977d0a390b3be1a4ad8cfab2e4dd3af3"
LOG4CPLUS_LINK="http://sourceforge.net/projects/log4cplus/files/log4cplus-stable/1.0.4/log4cplus-1.0.4.tar.bz2"
LOG4CPLUS_INSTALL_DIR="log4cplus-1.0.4"

GMOCK_TARBALL="gmock-1.6.0.zip"
GMOCK_MD5="f547f47321ca88d3965ca2efdcc2a3c1"
GMOCK_LINK="http://googlemock.googlecode.com/files/gmock-1.6.0.zip"
GMOCK_INSTALL_DIR="gmock-1.6.0"
GTEST_INSTALL_DIR="gtest-1.6.0"

PROTOBUF_TARBALL="protobuf-2.4.1.tar.gz"
PROTOBUF_MD5="dc84e9912ea768baa1976cb7bbcea7b5"
PROTOBUF_LINK="http://protobuf.googlecode.com/files/protobuf-2.4.1.tar.gz"
PROTOBUF_INSTALL_DIR="protobuf-2.4.1"

THRIFT_TARBALL="thrift-0.8.0.tar.gz"
THRIFT_MD5="d29dfcd38d476cbc420b6f4d80ab966c"
THRIFT_LINK="https://dist.apache.org/repos/dist/release/thrift/0.8.0/thrift-0.8.0.tar.gz"
THRIFT_INSTALL_DIR="thrift-0.8.0"

URIPARSER_TARBALL="uriparser-0.7.7.tar.bz2"
URIPARSER_MD5="2da950ef006be5a842dcc383cbbeaa78"
URIPARSER_LINK="http://downloads.sourceforge.net/project/uriparser/Sources/0.7.7/uriparser-0.7.7.tar.bz2"
URIPARSER_INSTALL_DIR="uriparser-0.7.7"

ZEROMQ_TARBALL="zeromq-3.2.2.tar.gz"
ZEROMQ_MD5="df68431d9300da84a1a5f9a2784e33de"
ZEROMQ_LINK="http://download.zeromq.org/zeromq-3.2.2.tar.gz"
ZEROMQ_INSTALL_DIR="zeromq-3.2.2"

ZEROMQ_BINDING_TARBALL="zmq.hpp"
ZEROMQ_BINDING_MD5="ee01fea5e2a069f936dc1d8e94496f3d"
ZEROMQ_BINDING_LINK="https://raw.github.com/zeromq/cppzmq/master/zmq.hpp"
ZEROMQ_BINDING_INSTALL_DIR="zmq"

OPENSLP_TARBALL="openslp-1.2.1.tar.gz"
OPENSLP_MD5="ff9999d1b44017281dd00ed2c4d32330"
OPENSLP_LINK="http://sourceforge.net/projects/openslp/files/OpenSLP/1.2.1/openslp-1.2.1.tar.gz"
OPENSLP_INSTALL_DIR="openslp-1.2.1"

###############################################################################
# Download the package
#
# Parameters:
#    $1 - tar-ball name
#    $2 - expected MD5
#    $3 - link to download
###############################################################################
get_packet ()
{
	if [[ -e $DOWNLOAD_DIR/$1 ]]; then
		if [[ `md5sum $DOWNLOAD_DIR/$1 | cut -d " " -f 1` == $2 ]]; then
			echo "Found already downloaded $1";
			return 0;
		else
			echo "Found a $1, but MD5 sum doesn't match";
			echo `md5sum $DOWNLOAD_DIR/$1 | cut -d " " -f 1`;
			rm -f $DOWNLOAD_DIR/$1;
		fi
	fi

	wget --no-check-certificate $3 -P $DOWNLOAD_DIR;

	return 0;
}

removeLibDir(){
	if [[ -z $LIB_DIR ]]; then
		echo "ERROR: Root library directory (LIB_DIR) is empty";
		exit -1;
	fi
	if [[ -z $1 ]]; then
		echo "ERROR: Library directory is empty";
		exit -1;
	fi
	if [[ -d $LIB_DIR/$1 ]]; then
		rm -rf $LIB_DIR/$1;
	fi
}

install_boost ()
{
	# Check if BOOST is already built
	 if [[ -d $LIB_DIR/$BOOST_INSTALL_DIR ]]; then
		echo "Boost is already built: $LIB_DIR/$BOOST_INSTALL_DIR";
		return 0;
	fi

	# unpack
	echo Unpacking...
	tar -C $BUILD_DIR -xzf $DOWNLOAD_DIR/$BOOST_TARBALL

	# build
	cd $BUILD_DIR
	mv $BOOST_INSTALL_DIR* $BOOST_INSTALL_DIR
	cd $BOOST_INSTALL_DIR
	./bootstrap.sh --without-libraries=python
	./b2 -sNO_BZIP2=1 -sNO_ZLIB=1

	if [[ $? != 0 ]]; then
		echo "Boost build failed."
		exit -1;
	fi

	cd ../..

	# install
	removeLibDir $BOOST_INSTALL_DIR
	mkdir -p $LIB_DIR/$BOOST_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$BOOST_INSTALL_DIR/lib/debug
	
	cp $BUILD_DIR/$BOOST_INSTALL_DIR/stage/lib/*.* $LIB_DIR/$BOOST_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$BOOST_INSTALL_DIR/stage/lib/*.* $LIB_DIR/$BOOST_INSTALL_DIR/lib/release
	strip $LIB_DIR/$BOOST_INSTALL_DIR/lib/release/*

	mkdir -p $LIB_DIR/$BOOST_INSTALL_DIR/include
	cp -a $BUILD_DIR/$BOOST_INSTALL_DIR/boost $LIB_DIR/$BOOST_INSTALL_DIR/include

	return 0;
}

install_cppunit ()
{
	# Check if CPPUnit is already built
	 if [[ -d $LIB_DIR/$CPPUNIT_INSTALL_DIR ]]; then
		echo "CppUnit is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xzf $DOWNLOAD_DIR/$CPPUNIT_TARBALL

	# build
	cd $BUILD_DIR/$CPPUNIT_INSTALL_DIR
	./configure
	make
	if [[ $? != 0 ]]; then
		echo "CPPUnit build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $CPPUNIT_INSTALL_DIR
	mkdir -p $LIB_DIR/$CPPUNIT_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$CPPUNIT_INSTALL_DIR/lib/debug

	cp $BUILD_DIR/$CPPUNIT_INSTALL_DIR/src/cppunit/.libs/*.* $LIB_DIR/$CPPUNIT_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$CPPUNIT_INSTALL_DIR/src/cppunit/.libs/*.* $LIB_DIR/$CPPUNIT_INSTALL_DIR/lib/release
	strip $LIB_DIR/$CPPUNIT_INSTALL_DIR/lib/release/*
	
	mkdir -p $LIB_DIR/$CPPUNIT_INSTALL_DIR/include
	cp -a $BUILD_DIR/$CPPUNIT_INSTALL_DIR/include/cppunit $LIB_DIR/$CPPUNIT_INSTALL_DIR/include
}

install_log4cplus ()
{
	# Check if Log4CPlus is already built
	 if [[ -d $LIB_DIR/$LOG4CPLUS_INSTALL_DIR ]]; then
		echo "Log4CPlus is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xjf $DOWNLOAD_DIR/$LOG4CPLUS_TARBALL

	# build
	cd $BUILD_DIR/$LOG4CPLUS_INSTALL_DIR
	./configure CXXFLAGS="-D_UNICODE -DUNICODE"
	make
	if [[ $? != 0 ]]; then
		echo "Log4CPlus build failed."
		exit -1;
	fi
	cd ../..
	
	removeLibDir $LOG4CPLUS_INSTALL_DIR
	mkdir -p $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/lib/debug
	
	cp $BUILD_DIR/$LOG4CPLUS_INSTALL_DIR/src/.libs/*.* $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$LOG4CPLUS_INSTALL_DIR/src/.libs/*.* $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/lib/release
	strip $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/lib/release/*

	mkdir -p $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/include
	cp -a $BUILD_DIR/$LOG4CPLUS_INSTALL_DIR/include/log4cplus $LIB_DIR/$LOG4CPLUS_INSTALL_DIR/include
}

install_gmock ()
{
	# Check if GMock is already built
	 if [[ -d $LIB_DIR/$GMOCK_INSTALL_DIR ]]; then
		echo "GMock is already built";
		return 0;
	fi

	# unpack
	unzip -d $BUILD_DIR $DOWNLOAD_DIR/$GMOCK_TARBALL
	
	# build
	cd $BUILD_DIR/$GMOCK_INSTALL_DIR
	./configure
	make
	if [[ $? != 0 ]]; then
		echo "GMock build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $GMOCK_INSTALL_DIR
	removeLibDir $GTEST_INSTALL_DIR
	mkdir -p $LIB_DIR/$GMOCK_INSTALL_DIR/lib/debug
	mkdir -p $LIB_DIR/$GMOCK_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$GTEST_INSTALL_DIR/lib/debug
	mkdir -p $LIB_DIR/$GTEST_INSTALL_DIR/lib/release

	# gmock
	cp $BUILD_DIR/$GMOCK_INSTALL_DIR/lib/.libs/*.* $LIB_DIR/$GMOCK_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$GMOCK_INSTALL_DIR/lib/.libs/*.* $LIB_DIR/$GMOCK_INSTALL_DIR/lib/release
	strip $LIB_DIR/$GMOCK_INSTALL_DIR/lib/release/*

	mkdir -p $LIB_DIR/$GMOCK_INSTALL_DIR/include
	cp -a $BUILD_DIR/$GMOCK_INSTALL_DIR/include/gmock $LIB_DIR/$GMOCK_INSTALL_DIR/include

	# gtest
	cp $BUILD_DIR/$GMOCK_INSTALL_DIR/gtest/lib/.libs/*.* $LIB_DIR/$GTEST_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$GMOCK_INSTALL_DIR/gtest/lib/.libs/*.* $LIB_DIR/$GTEST_INSTALL_DIR/lib/release
	strip $LIB_DIR/$GTEST_INSTALL_DIR/lib/release/*

	mkdir -p $LIB_DIR/$GTEST_INSTALL_DIR/include
	cp -a $BUILD_DIR/$GMOCK_INSTALL_DIR/gtest/include/gtest $LIB_DIR/$GTEST_INSTALL_DIR/include
}

install_protobuf ()
{
	# Check if Protobuf is already built
	 if [[ -d $LIB_DIR/$PROTOBUF_INSTALL_DIR ]]; then
		echo "Protobuf is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xzf $DOWNLOAD_DIR/$PROTOBUF_TARBALL

	# build
	cd $BUILD_DIR/$PROTOBUF_INSTALL_DIR
	./configure
	make
	if [[ $? != 0 ]]; then
		echo "Protobuf build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $PROTOBUF_INSTALL_DIR
	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/lib/debug

	cp $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/.libs/*.* $LIB_DIR/$PROTOBUF_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/.libs/*.* $LIB_DIR/$PROTOBUF_INSTALL_DIR/lib/release
	strip $LIB_DIR/$PROTOBUF_INSTALL_DIR/lib/release/*

	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf
	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf/compiler
	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf/io
	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf/stubs
	cp $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/google/protobuf/*.h $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf
	cp $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/google/protobuf/compiler/*.h $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf/compiler
	cp $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/google/protobuf/io/*.h $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf/io
	cp $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/google/protobuf/stubs/*.h $LIB_DIR/$PROTOBUF_INSTALL_DIR/include/google/protobuf/stubs

	mkdir -p $LIB_DIR/$PROTOBUF_INSTALL_DIR/bin
	cp -a $BUILD_DIR/$PROTOBUF_INSTALL_DIR/src/protoc $LIB_DIR/$PROTOBUF_INSTALL_DIR/bin
}

install_thrift ()
{
	# Check if Thrift is already built
	 if [[ -d $LIB_DIR/$THRIFT_INSTALL_DIR ]]; then
		echo "Thrift is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xzf $DOWNLOAD_DIR/$THRIFT_TARBALL

	# build
	cd $BUILD_DIR/$THRIFT_INSTALL_DIR
	./configure --without-python
	make
	if [[ $? != 0 ]]; then
		echo "Thrift build failed."
		exit -1;
	fi

	mkdir -p root
	make prefix=`pwd`/root install
	if [[ $? != 0 ]]; then
		echo "Thrift build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $THRIFT_INSTALL_DIR
	mkdir -p $LIB_DIR/$THRIFT_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$THRIFT_INSTALL_DIR/lib/debug

	cp $BUILD_DIR/$THRIFT_INSTALL_DIR/root/lib/*.* $LIB_DIR/$THRIFT_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$THRIFT_INSTALL_DIR/root/lib/*.* $LIB_DIR/$THRIFT_INSTALL_DIR/lib/release
	strip $LIB_DIR/$THRIFT_INSTALL_DIR/lib/release/*

	cp -a $BUILD_DIR/$THRIFT_INSTALL_DIR/root/include/ $LIB_DIR/$THRIFT_INSTALL_DIR/
}

install_uriparser ()
{
	# Check if URIParser is already built
	 if [[ -d $LIB_DIR/$URIPARSER_INSTALL_DIR ]]; then
		echo "URIParser is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xjf $DOWNLOAD_DIR/$URIPARSER_TARBALL

	# build
	cd $BUILD_DIR/$URIPARSER_INSTALL_DIR
	./configure --disable-test
	make
	if [[ $? != 0 ]]; then
		echo "URIParser build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $URIPARSER_INSTALL_DIR
	mkdir -p $LIB_DIR/$URIPARSER_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$URIPARSER_INSTALL_DIR/lib/debug

	cp $BUILD_DIR/$URIPARSER_INSTALL_DIR/.libs/*.* $LIB_DIR/$URIPARSER_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$URIPARSER_INSTALL_DIR/.libs/*.* $LIB_DIR/$URIPARSER_INSTALL_DIR/lib/release
	strip $LIB_DIR/$URIPARSER_INSTALL_DIR/lib/release/*

	cp -a $BUILD_DIR/$URIPARSER_INSTALL_DIR/include $LIB_DIR/$URIPARSER_INSTALL_DIR
}

install_zeromq ()
{
	# Check if ZeroMQ is already built
	 if [[ -d $LIB_DIR/$ZEROMQ_INSTALL_DIR ]]; then
		echo "ZeroMQ is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xzf $DOWNLOAD_DIR/$ZEROMQ_TARBALL
	
	# build
	cd $BUILD_DIR/$ZEROMQ_INSTALL_DIR
	./configure
	make
	if [[ $? != 0 ]]; then
		echo "ZeroMQ build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $ZEROMQ_INSTALL_DIR
	mkdir -p $LIB_DIR/$ZEROMQ_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$ZEROMQ_INSTALL_DIR/lib/debug
	
	cp $BUILD_DIR/$ZEROMQ_INSTALL_DIR/src/.libs/*.* $LIB_DIR/$ZEROMQ_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$ZEROMQ_INSTALL_DIR/src/.libs/*.* $LIB_DIR/$ZEROMQ_INSTALL_DIR/lib/release

	cp -a $BUILD_DIR/$ZEROMQ_INSTALL_DIR/include $LIB_DIR/$ZEROMQ_INSTALL_DIR
}

install_zeromq_binding ()
{
	cp -a $DOWNLOAD_DIR/$ZEROMQ_BINDING_TARBALL $LIB_DIR/$ZEROMQ_INSTALL_DIR/include
}

install_openslp ()
{
	# Check if OpenSLP is already built
	 if [[ -d $LIB_DIR/$OPENSLP_INSTALL_DIR ]]; then
		echo "OpenSLP is already built";
		return 0;
	fi

	# unpack
	tar -C $BUILD_DIR -xzf $DOWNLOAD_DIR/$OPENSLP_TARBALL
	
	# build
	cd $BUILD_DIR/$OPENSLP_INSTALL_DIR
	./configure
	make
	if [[ $? != 0 ]]; then
		echo "OpenSLP build failed."
		exit -1;
	fi
	cd ../..

	# install
	removeLibDir $OPENSLP_INSTALL_DIR
	mkdir -p $LIB_DIR/$OPENSLP_INSTALL_DIR/lib/release
	mkdir -p $LIB_DIR/$OPENSLP_INSTALL_DIR/lib/debug
	mkdir -p $LIB_DIR/$OPENSLP_INSTALL_DIR/include

	cp $BUILD_DIR/$OPENSLP_INSTALL_DIR/libslp/.libs/* $LIB_DIR/$OPENSLP_INSTALL_DIR/lib/debug
	cp $BUILD_DIR/$OPENSLP_INSTALL_DIR/libslp/.libs/* $LIB_DIR/$OPENSLP_INSTALL_DIR/lib/release

	cp $BUILD_DIR/$OPENSLP_INSTALL_DIR/libslp/*.h $LIB_DIR/$OPENSLP_INSTALL_DIR/include
}

###############################################################################
# Entry point to the main script:
###############################################################################

if [[ `uname -o` == "Cygwin" ]]; then
	ISCYGWIN=true;
fi

# Get the path to the "cpp" folder
if [[ ! $1 ]]; then
	echo "Error: no path to the sources given";
	exit 0;
fi

# Check for wget
if [[ ! -e "/usr/bin/wget" ]]; then
	echo "Error: please install wget";
	exit -1;
fi

# Remember current location
OLD_PATH=`pwd`
# Sources
SRC_DIR=$1
# Destination
if [[ ! $2 ]]; then
	DST_DIR=$OLD_PATH;
else
	DST_DIR=$2;
fi

# Where to download
DOWNLOAD_DIR="$DST_DIR/$DOWNLOAD_DIR"
# Where to build
BUILD_DIR="$DST_DIR/$BUILD_DIR"

# Where to store built libs
if [[ $ISCYGWIN ]]; then
	LIB_DIR="$SRC_DIR/3rdparty/x86_cygwin";
else
	LIB_DIR="$SRC_DIR/3rdparty/x86_linux";
fi


if [[ ! -d $DOWNLOAD_DIR ]]; then
	mkdir $DOWNLOAD_DIR;
fi

if [[ ! -d $BUILD_DIR ]]; then
	mkdir $BUILD_DIR;
fi

if [[ ! -d $LIB_DIR ]]; then
	mkdir $LIB_DIR;
fi

# Get and install 3rd-party libraries

# BOOST
get_packet $BOOST_TARBALL $BOOST_MD5 $BOOST_LINK
install_boost

# CppUnit
# get_packet $CPPUNIT_TARBALL $CPPUNIT_MD5 $CPPUNIT_LINK
# install_cppunit

# Log4CPluse
get_packet $LOG4CPLUS_TARBALL $LOG4CPLUS_MD5 $LOG4CPLUS_LINK
install_log4cplus

# GMock
get_packet $GMOCK_TARBALL $GMOCK_MD5 $GMOCK_LINK
install_gmock

# Protobuf
get_packet $PROTOBUF_TARBALL $PROTOBUF_MD5 $PROTOBUF_LINK
install_protobuf

# Thrift
# get_packet $THRIFT_TARBALL $THRIFT_MD5 $THRIFT_LINK
# install_thrift

# URIParser
# get_packet $URIPARSER_TARBALL $URIPARSER_MD5 $URIPARSER_LINK
# install_uriparser

# ZeroMQ
get_packet $ZEROMQ_TARBALL $ZEROMQ_MD5 $ZEROMQ_LINK;
install_zeromq;

# ZeroMQ Binding
get_packet $ZEROMQ_BINDING_TARBALL $ZEROMQ_BINDING_MD5 $ZEROMQ_BINDING_LINK
install_zeromq_binding

# OpenSLP
get_packet $OPENSLP_TARBALL $OPENSLP_MD5 $OPENSLP_LINK
install_openslp


cd $OLD_PATH

exit 0

