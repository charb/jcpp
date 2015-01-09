#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"

#include <iostream>

#define TEST_NAME "Native Inet Address"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	NativeNetFactory * factory = NativeFactory::getNativeNetFactory();

	try {
		int counter = 0;
		std::vector<NativeInetAddress> addresses;

		addresses.clear();
		counter = 0;
		logInfo("Getting local host Inet Address...");
		factory->getAllInetAddressesForLocalHost(addresses);
		for (std::vector<NativeInetAddress>::iterator it = addresses.begin(); it != addresses.end(); ++it) {
			if(counter == 0) {
				logInfo("Local host Inet address host name: %s", it->getHostName().getString().c_str());
			}
			logInfo("Local host Inet address host family [%d]: %s", counter, it->getFamily() == IPV4_FAMILY ? "IPv4" : "IPv6");
			logInfo("Local host Inet address host address [%d]: %s", counter, it->getHostAddress().getString().c_str());
			counter++;
		}

		printf("\n");
		logInfo("Getting local host Loopback Address...");
		NativeInetAddress loopbackAddress = factory->getLoopbackAddress();
		logInfo("Loopback Inet address host name: %s", loopbackAddress.getHostName().getString().c_str());
		logInfo("Loopback Inet address host family: %s", loopbackAddress.getFamily() == IPV4_FAMILY ? "IPv4" : "IPv6");
		logInfo("Loopback Inet address host address: %s", loopbackAddress.getHostAddress().getString().c_str());

		printf("\n");
		addresses.clear();
		counter = 0;
		NativeString serverHost("hp346srv");
		factory->getAllInetAddressesByName(addresses, serverHost);
		for (std::vector<NativeInetAddress>::iterator it = addresses.begin(); it != addresses.end(); ++it) {
			if(counter == 0) {
				logInfo("hp346srv Inet address host name: %s", it->getHostName().getString().c_str());
			}
			logInfo("hp346srv Inet address host family [%d]: %s", counter, it->getFamily() == IPV4_FAMILY ? "IPv4" : "IPv6");
			logInfo("hp346srv Inet address host address [%d]: %s", counter, it->getHostAddress().getString().c_str());
			counter++;
		}

		printf("\n");
		addresses.clear();
		counter = 0;
		NativeString serverHost2("172.21.27.213");
		factory->getAllInetAddressesByName(addresses, serverHost2);
		for (std::vector<NativeInetAddress>::iterator it = addresses.begin(); it != addresses.end(); ++it) {
			if(counter == 0) {
				logInfo("String 172.21.27.213 Inet address host name: %s", it->getHostName().getString().c_str());
			}
			logInfo("String 172.21.27.213 Inet address host family [%d]: %s", counter, it->getFamily() == IPV4_FAMILY ? "IPv4" : "IPv6");
			logInfo("String 172.21.27.213 Inet address host address [%d]: %s", counter, it->getHostAddress().getString().c_str());
			counter++;
		}

		printf("\n");
		jbyte address[4] = {172, 21, 27, 213};
		NativeInetAddress inetAddress = factory->getInetAddressByAddress(address, IPV4_FAMILY);
		logInfo("172.21.27.213 Inet address host name: %s", inetAddress.getHostName().getString().c_str());
		logInfo("172.21.27.213 Inet address host family: %s", inetAddress.getFamily() == IPV4_FAMILY ? "IPv4" : "IPv6");
		logInfo("172.21.27.213 Inet address host address: %s", inetAddress.getHostAddress().getString().c_str());

	} catch (NativeException& e) {
		logError("NativeException thrown Class = %s Method = %s Message = %s", e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str());
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
