#include "controller.h"

int main()
{
    controller ctr_{};
    ctr_.login("terry","terry12345");

    // testing the most complicated role: TA permissions
    auto req = "TA_special_permission";
    ctr_.send_request(req);
    ctr_.send_request("will_fail_request");
}
