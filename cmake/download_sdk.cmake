# set version for the X-Plane SDK
set (XP_SDK_VERSION 411)
set (XP_SDK_URL https://developer.x-plane.com/wp-content/plugins/code-sample-generation/sdk_zip_files/XPSDK${XP_SDK_VERSION}.zip)

# download and extract the SDK
include(FetchContent)
FetchContent_Declare(
    xpsdk
    URL ${XP_SDK_URL}
)
FetchContent_MakeAvailable(xpsdk)
