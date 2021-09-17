#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "Log.h"
#include "fmt/format.h"
#include <curl/curl.h>

struct InfluxDBContext {
    std::string host;
    std::string database;
    std::string user;
    std::string password;
};

InfluxDBContext influxDBContext;

template <class TValue>
bool SendMetric(InfluxDBContext context, std::string metric, TValue value) {
    bool error = false;
    CURL* curl = curl_easy_init();
    if(curl) {
        const auto now = std::chrono::system_clock::now();
        const int timestampInSeconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

        std::string url = fmt::format("{}/write?db={}&precision=s", context.host, context.database);
        std::string data = fmt::format("{} value={} {:d}", metric, value, timestampInSeconds);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            LOG_ERROR("server", curl_easy_strerror(res));
            error = true;
        }
        curl_easy_cleanup(curl);
    }

    return error;
}

bool SendMetric(InfluxDBContext context, std::string metric) {
    return SendMetric<int>(context, metric, 1);
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


class InfluxDBWorld : public WorldScript
{
public:
    InfluxDBWorld() : WorldScript("InfluxDBWorld") { }

    void OnStartup() override
    {
        SendMetric(influxDBContext, "server_startup");
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
            influxDBContext.host  = sConfigMgr->GetStringDefault("InfluxDB.Host", "http://127.0.0.1:8086");
            influxDBContext.database  = sConfigMgr->GetStringDefault("InfluxDB.Database", "azerothcore");
            influxDBContext.user  = sConfigMgr->GetStringDefault("InfluxDB.User", "");
            influxDBContext.password  = sConfigMgr->GetStringDefault("InfluxDB.Password", "");
        }
    }
};


void AddInfluxDBScripts()
{
    new InfluxDBConfiguration();
    new InfluxDBPlayer();
    new InfluxDBWorld();
}
