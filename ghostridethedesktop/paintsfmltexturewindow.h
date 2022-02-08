#ifndef PAINTSFMLTEXTUREWINDOW_H
#define PAINTSFMLTEXTUREWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <SFML/Graphics.hpp>

namespace Ui {
class PaintSFMLTextureWindow;
}

class PaintSFMLTextureWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaintSFMLTextureWindow(QWidget *parent = 0);
    ~PaintSFMLTextureWindow();

private:
    Ui::PaintSFMLTextureWindow *ui;
    // Create a new render-texture
    sf::RenderTexture texture;
    sf::Texture sprite_texture;
    sf::Sprite sprite;
    QTimer *timer;


    void renderTexture();


};

#endif // PAINTSFMLTEXTUREWINDOW_H
