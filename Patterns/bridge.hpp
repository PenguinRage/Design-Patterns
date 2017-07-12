#ifndef DESIGN_PATTERNS_BRIDGE_HPP
#define DESIGN_PATTERNS_BRIDGE_HPP

#include <string>

namespace patterns {

    class VideoGame {
    public:
        VideoGame() {}

        virtual std::string getGameTitle(std::string title) = 0;
    };

    class Bioshock : public VideoGame {
    public:
        Bioshock() {}

        ~Bioshock() {}

        std::string getGameTitle(std::string title) {
            return title;
        }
    };

    class Fable : public VideoGame {
    public:
        Fable() {}

        ~Fable() {}

        std::string getGameTitle(std::string title) {
            return title;
        }
    };

    class GameConsole {
    protected:
        VideoGame *m_game;

    public:
        GameConsole(VideoGame *videoGame) : m_game(videoGame) {}

        virtual ~GameConsole() { delete m_game; }

        virtual std::string play() = 0;

        virtual void load(VideoGame *video_game, std::string title) = 0;
    };


    class Xbox : public GameConsole {
    private:
        std::string m_title;

    public:
        Xbox(VideoGame *video_game, std::string title) : GameConsole(video_game), m_title(title) {}

        ~Xbox() {}

        std::string play() { return m_game->getGameTitle(m_title); }

        void load(VideoGame *video_game, std::string title) {
            delete m_game;
            m_game = video_game;
            m_title = title;
        }
    };


    class PlayStation : public GameConsole {
    private:
        std::string m_title;

    public:
        PlayStation(VideoGame *video_game, std::string title) : GameConsole(video_game), m_title(title) {}

        ~PlayStation() {}

        std::string play() { return m_game->getGameTitle(m_title); }

        void load(VideoGame *video_game, std::string title) {
            delete m_game;
            m_game = video_game;
            m_title = title;
        }
    };
}

#endif //DESIGN_PATTERNS_BRIDGE_HPP
