打包静态库/动态库
*************************************************************************************************
1. gcc编译
	1.1> -I dir     指定自定义的头文件目录
	1.2> -D xxxx    定义宏
	1.3> -c         生成二进制文件.o
	1.4> -Wall      输出警告信息
	1.5> -g         使用gdb调试
	1.6> libxxx.a   使用静态库中的函数
	1.7> -L lib -l xxx     -L指定静态库的目录 -l指定静态库的名字 



2. 静态库
	2.1> 命名规则    lib+库名+.a   例如： libtouch.a
	2.2> 生成静态库
			1. 生成.o    $ gcc -c *.c
			2. .o  --> libxxx.a    使用工具ar  $ar rcs libxxx.a  (all).o
	2.3> 发布静态库
			1. 静态库
			2. 头文件    暴露接口
	2.4> 查看静态库内容    nm libxxx.a   nm也可以查看可执行文件
	2.5> 静态库被打包到可执行文件中了，库的加载速度比较快，如果库代码修改，需要重新编译文件



3. 动态库（共享库） share object
	3.1> 命名规则    lib+库名+.so    例如： libdynamic.so
	3.2> 生成动态库
			1. 生成位置无关的代码 .o     $ gcc -fPIC -c *.c
			2. 将.o生成动态库           $ gcc -shared libxxx.so *.o
	3.3> 发布动态库
			1. libxxx.so
			2. 头文件
	3.4> 使用动态库    gcc dir/libxxx.so  -o ... -I (头文件目录)
	                  gcc -Ldir -lxxxx ...      // dir动态库所在的目录  xxxx动态库的名字
	3.5> ldd exe 查看可执行程序所依赖的动态库  动态连接器 /lib64/ld
	3.6> 动态链接器根据环境变量查找so库，   /lib   ---> 存放动态库
	      解决动态库找不到的方法：
	      		1. 将自己创建的动态库拷贝到/lib下面
	      		2. $export LD_LIBRARY_PATH=dir/.....      将自定义的so动态库路径加到环境变量LD_LIBRARY_PATH中
	      		3. $vim .bashrc  新增环境变量   export LD_LIBRARY_PATH=.../dir/.....
	      		   $source
	      		4. 动态链接器配置文件 #sudo vim /etc/ld.so.conf   更新文件 #sudo ldconfig -v




/******************************************编译生成静态库*********************************************/
生成静态库：
	1.  src/: $gcc -c *.c  -I../include     // 生成.o
		src/: $ar rcs libxxx.a *.o          // 生成静态库 .a
		src/: $nm libxxx.a                  // 查看静态库
		src/: $mv libxxx.a ../lib
/----
	|----main.c
	|----src/         源码存放目录
			|----sum.c
			|----sub.c
			|----div.c
	|----lib/         静态库
			|----libxxx.a
	|----include/     头文件
				|-----head.h
编译可main.c:  $ gcc main.c -o exe -Llib -ltouch -Iinclude

查看可执行文件： $ nm exe
	0000000000601034 B __bss_start
	0000000000601034 b completed.6344
	0000000000601030 D __data_start
	0000000000601030 W data_start
	0000000000400470 t deregister_tm_clones
	00000000004004e0 t __do_global_dtors_aux
	0000000000600e18 t __do_global_dtors_aux_fini_array_entry
	00000000004005f8 R __dso_handle
	0000000000600e28 d _DYNAMIC
	0000000000601034 D _edata
	0000000000601038 B _end
	00000000004005e4 T _fini
	0000000000400500 t frame_dummy
	0000000000600e10 t __frame_dummy_init_array_entry
	0000000000400768 r __FRAME_END__
	0000000000601000 d _GLOBAL_OFFSET_TABLE_
	                 w __gmon_start__
	00000000004003e0 T _init
	0000000000600e18 t __init_array_end
	0000000000600e10 t __init_array_start
	00000000004005f0 R _IO_stdin_used
	                 w _ITM_deregisterTMCloneTable
	                 w _ITM_registerTMCloneTable
	0000000000600e20 d __JCR_END__
	0000000000600e20 d __JCR_LIST__
	                 w _Jv_RegisterClasses
	00000000004005e0 T __libc_csu_fini
	0000000000400570 T __libc_csu_init
	                 U __libc_start_main@@GLIBC_2.2.5
	000000000040052d T main
	                 U printf@@GLIBC_2.2.5
	00000000004004a0 t register_tm_clones
	0000000000400440 T _start
	0000000000400558 T sum
	0000000000601038 D __TMC_END__




/******************************************编译生成动态库*********************************************/
1. src/:  gcc -fPIC -c *.c -I../include                  // 生成.o文件
   src/:  gcc -shared -fPIC -o libtouch.so  *.o          // 生成.so文件

   /: gcc main.c -o main -Llib -ltouch -Iinclude

编译生成可执行文件之后，直接运行可执行文件，会出现以下错误：
	./main: error while loading shared libraries: libtouch.so: cannot open shared object file: No such file or directory

解决方案：
	# sudo vim /etc/ld.so.conf
	# sudo ldconfig -v

/usr/lib64/mysql:
        libmysqlclient.so.18 -> libmysqlclient.so.18.0.0
/root/itcast/lib:
        libtouch.so -> libtouch.so
/lib:
/lib64:
        libnl-cli-3.so.200 -> libnl-cli-3.so.200.23.0
        libnsspem.so -> libnsspem.so
        p11-kit-trust.so -> libnssckbi.so
        libmemusage.so -> libmemusage.so
        libnss_myhostname.so.2 -> libnss_myhostname.so.2
        libcupsmime.so.1 -> libcupsmime.so.1
        libnettle.so.4 -> libnettle.so.4.7
        libsemanage.so.1 -> libsemanage.so.1
        libnss3.so -> libnss3.so
        libidn.so.11 -> libidn.so.11.6.11
        libmenuw.so.5 -> libmenuw.so.5.9
        libnss_mymachines.so.2 -> libnss_mymachines.so.2
        libnl-3.so.200 -> libnl-3.so.200.23.0
        libdns-export.so.100 -> libdns-export.so.100.1.1
        libss.so.2 -> libss.so.2.0
        libgomp.so.1 -> libgomp.so.1.0.0
        libdbus-glib-1.so.2 -> libdbus-glib-1.so.2.2.2
        libcap.so.2 -> libcap.so.2.22
        libslang.so.2 -> libslang.so.2.2.4
        libustr-1.0.so.1 -> libustr-1.0.so.1.0.4
        libsensors.so.4 -> libsensors.so.4.4.0
        libdevmapper.so.1.02 -> libdevmapper.so.1.02
        libnl-xfrm-3.so.200 -> libnl-xfrm-3.so.200.23.0
        libssl3.so -> libssl3.so
        libcupsimage.so.2 -> libcupsimage.so.2
        libgssapi_krb5.so.2 -> libgssapi_krb5.so.2.2
        libnm.so.0 -> libnm.so.0.1.0
        libpolkit-gobject-1.so.0 -> libpolkit-gobject-1.so.0.0.0
        libpwquality.so.1 -> libpwquality.so.1.0.2
        libGeoIP.so.1 -> libGeoIP.so.1.5.0
        libattr.so.1 -> libattr.so.1.1.0
        libgnutls.so.28 -> libgnutls.so.28.41.16
        libcurl.so.4 -> libcurl.so.4.3.0
        libpcap.so.1 -> libpcap.so.1.5.3
        libnssdbm3.so -> libnssdbm3.so
        libdrm_intel.so.1 -> libdrm_intel.so.1.0.0
        libjson-c.so.2 -> libjson-c.so.2.0.1
        libnss_hesiod.so.2 -> libnss_hesiod-2.17.so
        libnfnetlink.so.0 -> libnfnetlink.so.0.2.0
        libxtables.so.10 -> libxtables.so.10.0.0
        libmozjs-17.0.so -> libmozjs-17.0.so
        libm.so.6 -> libm-2.17.so
        libnsssysinit.so -> libnsssysinit.so
        libnl-nf-3.so.200 -> libnl-nf-3.so.200.23.0
        libebtc.so -> libebtc.so
        libpipeline.so.1 -> libpipeline.so.1.2.3
        libldap_r-2.4.so.2 -> libldap_r-2.4.so.2.10.3
        libgettextlib-0.18.2.so -> libgettextlib-0.18.2.so
        libsystemd-journal.so.0 -> libsystemd-journal.so.0.11.5
        libfreebl3.so -> libfreebl3.so
        libformw.so.5 -> libformw.so.5.9
        libcroco-0.6.so.3 -> libcroco-0.6.so.3.0.1
        libplds4.so -> libplds4.so
        libjansson.so.4 -> libjansson.so.4.4.0
        libsystemd.so.0 -> libsystemd.so.0.6.0
        libassuan.so.0 -> libassuan.so.0.4.0
        libext2fs.so.2 -> libext2fs.so.2.4
        libqrencode.so.3 -> libqrencode.so.3.4.1
        libuuid.so.1 -> libuuid.so.1.3.0
        libmagic.so.1 -> libmagic.so.1.0.0
        libgpg-error.so.0 -> libgpg-error.so.0.10.0
        libssl.so.10 -> libssl.so.1.0.1e
        ld-linux-x86-64.so.2 -> ld-2.17.so
        libverto.so.1 -> libverto.so.1.0.0
        libsoup-gnome-2.4.so.1 -> libsoup-gnome-2.4.so.1.7.0
        libmpfr.so.4 -> libmpfr.so.4.1.1
        libfreeblpriv3.so -> libfreeblpriv3.so
        libmpc.so.3 -> libmpc.so.3.0.0
        libnl-genl-3.so.200 -> libnl-genl-3.so.200.23.0
        libcupsppdc.so.1 -> libcupsppdc.so.1
        libfipscheck.so.1 -> libfipscheck.so.1.2.1
        libgettextsrc-0.18.2.so -> libgettextsrc-0.18.2.so
        libipset.so.3 -> libipset.so.3.1.0
        libe2p.so.2 -> libe2p.so.2.3
        libpanel.so.5 -> libpanel.so.5.9
        libcom_err.so.2 -> libcom_err.so.2.1
        libjson.so.0 -> libjson.so.0.1.0
        libgmp.so.10 -> libgmp.so.10.2.0
        libply.so.2 -> libply.so.2.1.0
        libcrypto.so.10 -> libcrypto.so.1.0.1e
        libip4tc.so.0 -> libip4tc.so.0.1.0
        libssh2.so.1 -> libssh2.so.1.0.1
        libncurses++.so.5 -> libncurses++.so.5.9
        libpcre16.so.0 -> libpcre16.so.0.2.0
        libslapi-2.4.so.2 -> libslapi-2.4.so.2.10.3
        libgettextpo.so.0 -> libgettextpo.so.0.5.2
        libcupscgi.so.1 -> libcupscgi.so.1
        libelf.so.1 -> libelf-0.166.so
        libgpgme-pthread.so.11 -> libgpgme-pthread.so.11.8.1
        libhogweed.so.2 -> libhogweed.so.2.5
        libgssrpc.so.4 -> libgssrpc.so.4.2
        libp11-kit.so.0 -> libp11-kit.so.0.0.0
        libdbus-1.so.3 -> libdbus-1.so.3.7.4
        libisccfg-export.so.90 -> libisccfg-export.so.90.0.7
        libnssutil3.so -> libnssutil3.so
        libedit.so.0 -> libedit.so.0.0.42
        libGeoIPUpdate.so.0 -> libGeoIPUpdate.so.0.0.0
        libplc4.so -> libplc4.so
        libutil.so.1 -> libutil-2.17.so
        libnspr4.so -> libnspr4.so
        libprocps.so.4 -> libprocps.so.4.0.0
        liblua-5.1.so -> liblua-5.1.so
        libnl-idiag-3.so.200 -> libnl-idiag-3.so.200.23.0
        libsoup-2.4.so.1 -> libsoup-2.4.so.1.7.0
        libpcprofile.so -> libpcprofile.so
        libgmodule-2.0.so.0 -> libgmodule-2.0.so.0.4600.2
        libtspi.so.1 -> libtspi.so.1.2.0
        libsmime3.so -> libsmime3.so
        libstdc++.so.6 -> libstdc++.so.6.0.19
        libpcre32.so.0 -> libpcre32.so.0.0.0
        libnewt.so.0.52 -> libnewt.so.0.52.15
        libtic.so.5 -> libtic.so.5.9
        libBrokenLocale.so.1 -> libBrokenLocale-2.17.so
        libtinfo.so.5 -> libtinfo.so.5.9
        libpam.so.0 -> libpam.so.0.83.1
        libnuma.so.1 -> libnuma.so.1
        libmenu.so.5 -> libmenu.so.5.9
        libncurses.so.5 -> libncurses.so.5.9
        libthread_db.so.1 -> libthread_db-1.0.so
        libavahi-client.so.3 -> libavahi-client.so.3.2.9
        libpython2.7.so.1.0 -> libpython2.7.so.1.0
        libgmpxx.so.4 -> libgmpxx.so.4.4.0
        libgpgme.so.11 -> libgpgme.so.11.8.1
        libcrypt.so.1 -> libcrypt-2.17.so
        libmodman.so.1 -> libmodman.so.1.0.0
        librpmsign.so.1 -> librpmsign.so.1.2.2
        libgio-2.0.so.0 -> libgio-2.0.so.0.4600.2
        libgcrypt.so.11 -> libgcrypt.so.11.8.2
        libauparse.so.0 -> libauparse.so.0.0.0
        libpci.so.3 -> libpci.so.3.5.1
        libgudev-1.0.so.0 -> libgudev-1.0.so.0.2.0
        libsystemd-login.so.0 -> libsystemd-login.so.0.9.3
        libpcreposix.so.0 -> libpcreposix.so.0.0.1
        libpcre.so.1 -> libpcre.so.1.2.0
        libform.so.5 -> libform.so.5.9
        libestr.so.0 -> libestr.so.0.0.0
        libcryptsetup.so.4 -> libcryptsetup.so.4.7.0
        libply-boot-client.so.2 -> libply-boot-client.so.2.1.0
        librpmbuild.so.3 -> librpmbuild.so.3.2.2
        libanl.so.1 -> libanl-2.17.so
        libkrb5.so.3 -> libkrb5.so.3.3
        libutempter.so.0 -> libutempter.so.1.1.6
        libnss_files.so.2 -> libnss_files-2.17.so
        libsepol.so.1 -> libsepol.so.1
        libgcc_s.so.1 -> libgcc_s-4.8.5-20150702.so.1
        libnss_db.so.2 -> libnss_db-2.17.so
        libasm.so.1 -> libasm-0.166.so
        libdrm.so.2 -> libdrm.so.2.4.0
        libsnappy.so.1 -> libsnappy.so.1.1.4
        libsystemd-daemon.so.0 -> libsystemd-daemon.so.0.0.12
        liblzo2.so.2 -> liblzo2.so.2.0.0
        libkrad.so.0 -> libkrad.so.0.0
        libpciaccess.so.0 -> libpciaccess.so.0.11.1
        libkeyutils.so.1 -> libkeyutils.so.1.5
        libgthread-2.0.so.0 -> libgthread-2.0.so.0.4600.2
        libpopt.so.0 -> libpopt.so.0.0.0
        libblkid.so.1 -> libblkid.so.1.1.0
        libsoftokn3.so -> libsoftokn3.so
        libasprintf.so.0 -> libasprintf.so.0.0.0
        libbz2.so.1 -> libbz2.so.1.0.6
        libparted.so.2 -> libparted.so.2.0.0
        libreadline.so.6 -> libreadline.so.6.2
        libexpat.so.1 -> libexpat.so.1.6.0
        libselinux.so.1 -> libselinux.so.1
        libcrack.so.2 -> libcrack.so.2.9.0
        libnl-route-3.so.200 -> libnl-route-3.so.200.23.0
        libnetfilter_conntrack.so.3 -> libnetfilter_conntrack.so.3.6.0
        libparted-fs-resize.so.0 -> libparted-fs-resize.so.0.0.0
        libpanelw.so.5 -> libpanelw.so.5.9
        libteamdctl.so.0 -> libteamdctl.so.0.1.5
        libdrm_nouveau.so.2 -> libdrm_nouveau.so.2.0.0
        libhistory.so.6 -> libhistory.so.6.2
        libresolv.so.2 -> libresolv-2.17.so
        libasound.so.2 -> libasound.so.2.0.0
        libncursesw.so.5 -> libncursesw.so.5.9
        libpam_misc.so.0 -> libpam_misc.so.0.82.0
        libip6tc.so.0 -> libip6tc.so.0.1.0
        libc.so.6 -> libc-2.17.so
        libsqlite3.so.0 -> libsqlite3.so.0.8.6
        libxml2.so.2 -> libxml2.so.2.9.1
        libglib-2.0.so.0 -> libglib-2.0.so.0.4600.2
        libteam.so.5 -> libteam.so.5.3.4
        libgdbm.so.4 -> libgdbm.so.4.0.0
        libsasl2.so.3 -> libsasl2.so.3.0.0
        libz.so.1 -> libz.so.1.2.7
        libsysfs.so.2 -> libsysfs.so.2.0.1
        librt.so.1 -> librt-2.17.so
        libiptc.so.0 -> libiptc.so.0.0.0
        libgpm.so.2 -> libgpm.so.2.1.0
        libdl.so.2 -> libdl-2.17.so
        libisc-export.so.95 -> libisc-export.so.95.2.1
        libbfd-2.25.1-22.base.el7.so -> libbfd-2.25.1-22.base.el7.so
        libirs-export.so.90 -> libirs-export.so.90.0.1
        libcpupower.so.0 -> libcpupower.so.0.0.0
        libply-splash-core.so.2 -> libply-splash-core.so.2.1.0
        libunistring.so.0 -> libunistring.so.0.1.2
        libpcrecpp.so.0 -> libpcrecpp.so.0.0.0
        libkrb5support.so.0 -> libkrb5support.so.0.1
        libdaemon.so.0 -> libdaemon.so.0.5.0
        libfreetype.so.6 -> libfreetype.so.6.10.0
        libffi.so.6 -> libffi.so.6.0.1
        libpolkit-agent-1.so.0 -> libpolkit-agent-1.so.0.0.0
        libdw.so.1 -> libdw-0.166.so
        libnss_nisplus.so.2 -> libnss_nisplus-2.17.so
        libhandle.so.1 -> libhandle.so.1.0.3
        libndp.so.0 -> libndp.so.0.0.0
        libnss_compat.so.2 -> libnss_compat-2.17.so
        libgdbm_compat.so.4 -> libgdbm_compat.so.4.0.0
        libldap-2.4.so.2 -> libldap-2.4.so.2.10.3
        libncurses++w.so.5 -> libncurses++w.so.5.9
        libk5crypto.so.3 -> libk5crypto.so.3.1
        libnss_nis.so.2 -> libnss_nis-2.17.so
        libgobject-2.0.so.0 -> libgobject-2.0.so.0.4600.2
        libdb-5.3.so -> libdb-5.3.so
        libcap-ng.so.0 -> libcap-ng.so.0.0.0
        libcidn.so.1 -> libcidn-2.17.so
        libkmod.so.2 -> libkmod.so.2.2.10
        libacl.so.1 -> libacl.so.1.1.0
        libtasn1.so.6 -> libtasn1.so.6.2.3
        libdrm_amdgpu.so.1 -> libdrm_amdgpu.so.1.0.0
        libwrap.so.0 -> libwrap.so.0.7.6
        libSegFault.so -> libSegFault.so
        libgirepository-1.0.so.1 -> libgirepository-1.0.so.1.0.0
        libdrm_radeon.so.1 -> libdrm_radeon.so.1.0.1
        libaudit.so.1 -> libaudit.so.1.0.0
        liblzma.so.5 -> liblzma.so.5.2.2
        libomapi.so.0 -> libomapi.so.0.0.0
        libuser.so.1 -> libuser.so.1.5.0
        liblber-2.4.so.2 -> liblber-2.4.so.2.10.3
        libkms.so.1 -> libkms.so.1.0.0
        libmnl.so.0 -> libmnl.so.0.1.0
        libcups.so.2 -> libcups.so.2
        libnsl.so.1 -> libnsl-2.17.so
        libpamc.so.0 -> libpamc.so.0.82.1
        librpmio.so.3 -> librpmio.so.3.2.2
        libnss_dns.so.2 -> libnss_dns-2.17.so
        libkdb5.so.8 -> libkdb5.so.8.0
        librpm.so.3 -> librpm.so.3.2.2
        libmount.so.1 -> libmount.so.1.1.0
        libopts.so.25 -> libopts.so.25.15.0
        libdhcpctl.so.0 -> libdhcpctl.so.0.0.0
        libavahi-common.so.3 -> libavahi-common.so.3.5.3
        libpthread.so.0 -> libpthread-2.17.so
        libpth.so.20 -> libpth.so.20.0.27
        libopcodes-2.25.1-22.base.el7.so -> libopcodes-2.25.1-22.base.el7.so
        libbtrfs.so.0 -> libbtrfs.so.0.1
        libudev.so.1 -> libudev.so.1.6.2
        libproxy.so.1 -> libproxy.so.1.0.0
        libsystemd-id128.so.0 -> libsystemd-id128.so.0.0.28
/lib/sse2: (hwcap: 0x0000000004000000)
/lib64/tls: (hwcap: 0x8000000000000000)
/lib64/sse2: (hwcap: 0x0000000004000000)