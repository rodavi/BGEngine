#pragma once

class GameObject {
public:
    virtual void draw()=0;
    virtual void update(double dt)=0;
    virtual void render(double alpha)=0;

    int getId() const { return m_id; }
    bool isDead() const { return m_isDead; }
    void markAsDead() { m_isDead = true; }
    
    // El destructor debe ser virtual para asegurar una limpieza correcta [3]
    virtual ~GameObject() {} 

protected:
    GameObject(int id) : m_id(id) {}

private:
    // Atributos del objeto
    int m_id; // Identificador único del objeto
    bool m_isDead = false; // Estado de vida del objeto
    // Otros atributos...
};
