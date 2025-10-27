# SPDX-FileCopyrightText: 2025 Clockwise Integration
# SPDX-License-Identifier: MIT

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select
from esphome.const import (
    CONF_ID,
    CONF_ENTITY_CATEGORY,
    ENTITY_CATEGORY_CONFIG,
)

from .. import clockwise_hub75_ns, ClockwiseHUB75, CONF_CLOCKWISE_HUB75_ID

DEPENDENCIES = ["clockwise_hub75"]

ClockwiseSelect = clockwise_hub75_ns.class_("ClockwiseSelect", select.Select, cg.Component)

CONFIG_SCHEMA = select.SELECT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(ClockwiseSelect),
    cv.GenerateID(CONF_CLOCKWISE_HUB75_ID): cv.use_id(ClockwiseHUB75),
    cv.Optional(CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG): cv.entity_category,
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    # Define the clockface options
    options = ["Pacman", "Mario", "Clock"]
    await select.register_select(var, config, options=options)
    
    parent = await cg.get_variable(config[CONF_CLOCKWISE_HUB75_ID])
    cg.add(var.set_clockwise_hub75(parent))