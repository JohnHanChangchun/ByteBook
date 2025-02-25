高效率C++序列化库
支持基础数据类型：int float double bool等
STL：std::string
OpenCV：cv::Mat

这是初代版本，已迭代支持重载流控制符>> << 暂未上传，后续优化后上传

目前所有大型项目的数据，都可以转为基础数据类型与字符串类型
特殊第三方库数据类型（如OpenCV）可以定制优化，后续会增加更多数据类
目前暂不使用Archive函数名统一序列化与反序列化接口，所以OpenMode暂时无用（个人认为名字不一样serialize、deserialize，可以增加代码可读性）