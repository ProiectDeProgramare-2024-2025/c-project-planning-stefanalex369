#include "Task.h"
#include <sstream>

Task::Task(int _id, const std::string& desc, bool comp)
    : id(_id), description(desc), completed(comp) {}

std::string Task::to_string() const {
    std::ostringstream oss;
    oss << id << " - [" << (completed ? 'x' : ' ') << "] " << description;
    return oss.str();
}

Task Task::from_string(const std::string& line) {
    int id;
    char status;
    std::string desc;

    std::size_t first_dash = line.find(" - [");
    if (first_dash == std::string::npos) return Task(0, "", false);

    id = std::stoi(line.substr(0, first_dash));

    std::size_t status_pos = line.find('[', first_dash);
    if (status_pos == std::string::npos || status_pos + 2 >= line.size())
        return Task(id, "", false);

    status = line[status_pos + 1];

    std::size_t desc_start = line.find("] ", status_pos);
    if (desc_start != std::string::npos)
        desc = line.substr(desc_start + 1);
    else
        desc = "";

    return Task(id, desc, status == 'x');
}

