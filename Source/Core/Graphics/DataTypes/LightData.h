#pragma once

namespace QwerkE {

    struct LightData
    {
        vec3 position;

        vec3 ambient = vec3(1, 1, 1);
        vec3 diffuse = vec3(1, 1, 1);
        vec3 specular = vec3(1, 1, 1);
    };

}
