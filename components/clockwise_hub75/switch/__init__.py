# SPDX-FileCopyrightText: 2025 Clockwise Integration
# SPDX-License-Identifier: MIT

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    CONF_ID,
    CONF_ENTITY_CATEGORY,
    ENTITY_CATEGORY_CONFIG,
    ICON_POWER,
)

from .. import clockwise_hub75_ns, ClockwiseHUB75, CONF_CLOCKWISE_HUB75_ID

DEPENDENCIES = ["clockwise_hub75"]

ClockwiseSwitch = clockwise_hub75_ns.class_("ClockwiseSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(ClockwiseSwitch),
    cv.GenerateID(CONF_CLOCKWISE_HUB75_ID): cv.use_id(ClockwiseHUB75),
    cv.Optional(CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG): cv.entity_category,
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await switch.register_switch(var, config)
    
    parent = await cg.get_variable(config[CONF_CLOCKWISE_HUB75_ID])
    cg.add(var.set_clockwise_hub75(parent))