# SPDX-FileCopyrightText: 2025 Clockwise Integration  
# SPDX-License-Identifier: MIT

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ID,
    CONF_ENTITY_CATEGORY,
    ENTITY_CATEGORY_CONFIG,
    ICON_BRIGHTNESS_5,
)

from .. import clockwise_hub75_ns, ClockwiseHUB75, CONF_CLOCKWISE_HUB75_ID

DEPENDENCIES = ["clockwise_hub75"]

ClockwiseBrightness = clockwise_hub75_ns.class_("ClockwiseBrightness", number.Number, cg.Component)

CONFIG_SCHEMA = number.NUMBER_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(ClockwiseBrightness),
    cv.GenerateID(CONF_CLOCKWISE_HUB75_ID): cv.use_id(ClockwiseHUB75),
    cv.Optional(CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG): cv.entity_category,
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await number.register_number(var, config, min_value=0, max_value=255, step=1)
    
    parent = await cg.get_variable(config[CONF_CLOCKWISE_HUB75_ID])
    cg.add(var.set_clockwise_hub75(parent))