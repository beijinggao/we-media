# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.libcef_dll_wrapper.Debug:
/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a:
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a


PostBuild.cefclient.Debug:
PostBuild.libcef_dll_wrapper.Debug: /Users/gaodong/Documents/mobile/we-media/src/cefclient/Debug/cefclient.app/Contents/MacOS/cefclient
/Users/gaodong/Documents/mobile/we-media/src/cefclient/Debug/cefclient.app/Contents/MacOS/cefclient:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Debug/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefclient/Debug/cefclient.app/Contents/MacOS/cefclient


PostBuild.cefclient_Helper.Debug:
PostBuild.libcef_dll_wrapper.Debug: /Users/gaodong/Documents/mobile/we-media/src/cefclient/Debug/cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper
/Users/gaodong/Documents/mobile/we-media/src/cefclient/Debug/cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Debug/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefclient/Debug/cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper


PostBuild.cefsimple.Debug:
PostBuild.libcef_dll_wrapper.Debug: /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Debug/cefsimple.app/Contents/MacOS/cefsimple
/Users/gaodong/Documents/mobile/we-media/src/cefsimple/Debug/cefsimple.app/Contents/MacOS/cefsimple:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Debug/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Debug/cefsimple.app/Contents/MacOS/cefsimple


PostBuild.cefsimple_Helper.Debug:
PostBuild.libcef_dll_wrapper.Debug: /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Debug/cefsimple\ Helper.app/Contents/MacOS/cefsimple\ Helper
/Users/gaodong/Documents/mobile/we-media/src/cefsimple/Debug/cefsimple\ Helper.app/Contents/MacOS/cefsimple\ Helper:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Debug/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Debug/cefsimple\ Helper.app/Contents/MacOS/cefsimple\ Helper


PostBuild.libcef_dll_wrapper.Release:
/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a:
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a


PostBuild.cefclient.Release:
PostBuild.libcef_dll_wrapper.Release: /Users/gaodong/Documents/mobile/we-media/src/cefclient/Release/cefclient.app/Contents/MacOS/cefclient
/Users/gaodong/Documents/mobile/we-media/src/cefclient/Release/cefclient.app/Contents/MacOS/cefclient:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Release/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefclient/Release/cefclient.app/Contents/MacOS/cefclient


PostBuild.cefclient_Helper.Release:
PostBuild.libcef_dll_wrapper.Release: /Users/gaodong/Documents/mobile/we-media/src/cefclient/Release/cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper
/Users/gaodong/Documents/mobile/we-media/src/cefclient/Release/cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Release/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefclient/Release/cefclient\ Helper.app/Contents/MacOS/cefclient\ Helper


PostBuild.cefsimple.Release:
PostBuild.libcef_dll_wrapper.Release: /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Release/cefsimple.app/Contents/MacOS/cefsimple
/Users/gaodong/Documents/mobile/we-media/src/cefsimple/Release/cefsimple.app/Contents/MacOS/cefsimple:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Release/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Release/cefsimple.app/Contents/MacOS/cefsimple


PostBuild.cefsimple_Helper.Release:
PostBuild.libcef_dll_wrapper.Release: /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Release/cefsimple\ Helper.app/Contents/MacOS/cefsimple\ Helper
/Users/gaodong/Documents/mobile/we-media/src/cefsimple/Release/cefsimple\ Helper.app/Contents/MacOS/cefsimple\ Helper:\
	/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Release/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework\
	/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a
	/bin/rm -f /Users/gaodong/Documents/mobile/we-media/src/cefsimple/Release/cefsimple\ Helper.app/Contents/MacOS/cefsimple\ Helper




# For each target create a dummy ruleso the target does not have to exist
/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Debug/libcef_dll_wrapper.a:
/Users/gaodong/Documents/mobile/we-media/libcef_dll_wrapper/Release/libcef_dll_wrapper.a:
/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Debug/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework:
/Users/gaodong/Documents/mobile/we-media/third_party/cef/cef_binary_3.3497.1827.ga4f7e36_macosx64/Release/Chromium\ Embedded\ Framework.framework/Chromium\ Embedded\ Framework:
