#include "klient.hh"

int klient::exec()
{
    Configuration Config;
    Reader reader;
    Set4LibInterfaces lib_handler;
    AbstractInterp4Command* command;
    std::istringstream stream;
    std::vector<std::thread> threads;
    std::string key;

    reader.init("commands.cmd");
    if (!reader.ReadFile("config/config.xml", Config))
        return 1;

    Scene scene(Config);
    Sender sender(&scene);
    if (!sender.OpenConnection())
        return 1;

    lib_handler.init(Config.libs);
    reader.execPreprocesor(stream);

    std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);

    while (stream >> key) {
        command = lib_handler.execute(key);

        if (lib_handler.isParallel() && command != nullptr) {
            command->ReadParams(stream);
            threads.push_back(std::thread(&AbstractInterp4Command::ExecCmd, command, &scene));
        } else if (!lib_handler.isParallel()) {
            for (size_t i = 0; i < threads.size(); ++i) {
                if (threads[i].joinable())
                    threads[i].join();
            }
            threads.clear();
        }
    }

    // Threads Join
    sender.Send("Close\n");
    sender.CancelCountinueLooping();
    for (size_t i = 0; i < threads.size(); ++i) {
        if (threads[i].joinable())
            threads[i].join();
    }
    Thread4Sending.join();

    return 0;
}
