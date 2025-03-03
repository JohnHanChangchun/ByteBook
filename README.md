# ByteBook
A high-efficiency serialization library 一个高效率的序列化库 
支持C++所有基础数据类型int short float double bool long等等。
最开始研发这个动态库时的基本目标是结局五千万颗芯片的结果数据能相较于Qt的QDataStream效率提升50%，实际效果提升达到序列化74%，反序列化97%。
并且为OpenCV的cv::Mat数据类型做了定制化处理。
核心思想是：
1.能不发生拷贝就不拷贝：例如构造直接传递buffer的引用作为成员
2.必须拷贝则减少重复性的动作，并且使用C风格的底层硬拷贝，而不调用臃肿的方法：例如使用memcpy而不是insert
3.避免循环：对于cv::Mat类型其实可以使用for循环遍历单个元素的值进行多次的序列化，但这样效率会很低，所以为cv::Mat开发定制序列化函数，直接拷贝data数据
