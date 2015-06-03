#include <CMdHandler.h>


static MdConfigure config;
static char buffer[1024*10];

int main(int argc,char * argv[]){
    // 导入配置信息
    CommandOption commandOption(argc,argv);
    if( commandOption.exists("--env") ) {
        // 使用环境变量
        config.loadFromEnvironment();
    } else {
        // 使用命令行参数
        config.loadFromCommandLine(commandOption);
    }

    for(int i = 0; i < config.instrumentCount; i++ ){
        std::cout << "config.instrumentIDArray[" << i << "]="
        << config.instrumentIDArray[i] << std::endl;
    }
}
