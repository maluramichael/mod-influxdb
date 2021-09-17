#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include <curl/curl.h>

struct InfluxDBContext {
    std::string host;
    std::string database;
    std::string user;
    std::string password;
};

InfluxDBContext influxDBContext;

void SendMetric(InfluxDBContext context, std::string metric) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, context.host);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
}

class InfluxDBPlayer : public PlayerScript
{

public:
    InfluxDBPlayer() : PlayerScript("InfluxDBPlayer") { }

    void OnLogin(Player* player) override
    {
        SendMetric(influxDBContext, "player_login");
    }
};

class InfluxDBConfiguration : public WorldScript
{
public:
    InfluxDBConfiguration() : WorldScript("InfluxDBConfiguration")
    {
    }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            influxDBContext.host  = sConfigMgr->GetBoolDefault("InfluxDB.Host", "127.0.0.1");
        }
    }
};


void AddInfluxDBScripts()
{
    new InfluxDBConfiguration();
    new InfluxDBPlayer();
}
