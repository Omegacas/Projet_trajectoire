% 1. On lit le tableau (en gardant tout en texte pour l'instant)
T = readtable('../trajectoire/OBSTACLE/Obstacles_1.csv', 'Delimiter', '|', 'ReadVariableNames', true);

% 2. On récupère la cellule de l'Obstacle_3 (la ligne 1 par exemple)
Nombre_obstacle=size(T)
Nombre_obstacle=Nombre_obstacle(2)
figure; % Ouvre une nouvelle fenêtre
hold on; % RESTE activé pour superposer tous les dessins
for i=1 : 2
    txt_obstacle = T{1, i} %on exrtrait le point de départ et d'arrivé
    matches = regexp(txt_obstacle{1}, '(?<x>[\d\.]+),(?<y>[\d\.]+)', 'names');
    matches.x;
    X = str2double({matches.x});
    Y = str2double({matches.y});
    disp([X' Y']);
    plot(X(1), Y(1), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
end
for i=3 : Nombre_obstacle-1
    col_index =  i; % On décale de 2 car il y a "Depart" et "Arrive" avant
    txt_obstacle = T{1, col_index} 
    matches = regexp(txt_obstacle{1}, '(?<x>[\d\.]+),(?<y>[\d\.]+)', 'names');
    matches.x;
    X = str2double({matches.x});
    Y = str2double({matches.y});
    disp([X' Y']);
    pgon=polyshape(X,Y);
    plot(pgon)
end
    txt_obstacle = T{1, Nombre_obstacle} %on exrtrait le point de départ et d'arrivé
    matches = regexp(txt_obstacle{1}, '(?<x>[\d\.]+),(?<y>[\d\.]+)', 'names');
    matches.x;
    X = str2double({matches.x});
    Y = str2double({matches.y});
    disp([X' Y']);
    plot(X, Y)