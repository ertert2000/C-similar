var config = {
    mode: "fixed_servers",
    rules: {
        singleProxy: {
            scheme: "https",
            host: "188.134.69.149",
            port: parseInt("40667")
        },
        bypassList: ["localhost"]
    }
};

chrome.proxy.settings.set({ value: config, scope: "regular" }, function () { });

chrome.webRequest.onAuthRequired.addListener(
    function (details) {
        return {
            authCredentials: {
                username: "851f66e5a7",
                password: "7e6aca5ae1"
            }
        };
    },
    { urls: ["<all_urls>"] },
    ["blocking"]
);
