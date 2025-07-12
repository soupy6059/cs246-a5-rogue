export module entity;

import decorator;
import observer;
import subject;
import component;

export class Entity:
    public Decorator, public Observer, public Subject, public Component {
};
