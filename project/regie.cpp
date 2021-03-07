#include "controller.h"

int main()
{
    controller ctr_{};
    ctr_.login("terry","terry12345");

    auto req = "TA_special_permission";
    ctr_.send_request(req);
    ctr_.send_request("will_fail_request");
}
